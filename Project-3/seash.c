#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#define LINE_SIZE 1024
#define MAX_ARGS 128
#define HISTORY_SUFFIX "/.seash_history"

void parse_args(char *str, char *result[], int len) {
    if (str == NULL || result == NULL || len <= 0) {
        return;
    }
    int count = 0;
    char *token = strtok(str, " \t\n");
    while (token != NULL && count < len - 1) {
        result[count] = token;
        count++;
        token = strtok(NULL, " \t\n");
    }
    result[count] = NULL;
}

void write_history(const char *history_path, char *args[]) {
    FILE *file = fopen(history_path, "a");
    if (file == NULL) {
        perror("open");
        exit(1);
    }
    for (int i = 0; args[i] != NULL; i++) {
        if (i > 0) {
            fputc(' ', file);
        }
        fprintf(file, "%s", args[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

void print_history(const char *history_path) {
    FILE *file = fopen(history_path, "r");
    if (file == NULL) {
        return; /* no history yet */
    }
    char line[LINE_SIZE];
    int line_number = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%d %s", line_number, line);
        line_number++;
    }
    fclose(file);
}

void clear_history(const char *history_path) {
    FILE *file = fopen(history_path, "w");
    if (file == NULL) {
        perror("open");
        exit(1);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: ./seash [script]\n");
        return 1;
    }

    FILE *input = stdin;
    int batch = 0;
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror(argv[1]);
            return 1;
        }
        batch = 1;
    }

    struct passwd *pw = getpwuid(getuid());
    const char *username = (pw != NULL) ? pw->pw_name : "you";
    const char *home_dir = (pw != NULL) ? pw->pw_dir : getenv("HOME");

    char history_path[LINE_SIZE];
    snprintf(history_path, sizeof(history_path), "%s%s", home_dir, HISTORY_SUFFIX);

    char prev_dir[LINE_SIZE]; 
    int has_prev = 0;

    char line[LINE_SIZE];
    char *args[MAX_ARGS];

    while (1) {
        if (batch) {
            if (fgets(line, sizeof(line), input) == NULL) {
                break; 
            }
        } else {
            char cwd[LINE_SIZE];
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                cwd[0] = '\0';
            }
            printf("%s@🐚 %s$ ", username, cwd);
            fflush(stdout);
            if (fgets(line, sizeof(line), input) == NULL) {
                break; 
            }
        }

        parse_args(line, args, MAX_ARGS);

        if (args[0] == NULL) {
            continue; 
        }

        if (!batch) {
            write_history(history_path, args);
        }

        int background = 0;
        int n = 0;
        while (args[n] != NULL) {
            n++;
        }
        if (n > 0 && strcmp(args[n - 1], "&") == 0) {
            background = 1;
            args[n - 1] = NULL;
            n--;
        }
        if (n == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            if (n != 1) {
                fprintf(stderr, "seash: Usage error\n");
                continue;
            }
            exit(EXIT_SUCCESS);
        }

        if (strcmp(args[0], "cd") == 0) {
            if (n > 2) {
                fprintf(stderr, "seash: Usage error\n");
                continue;
            }
            char cwd[LINE_SIZE];
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                cwd[0] = '\0';
            }
            if (n == 1) {
                if (chdir(home_dir) != 0) {
                    perror("cd");
                    continue;
                }
                strcpy(prev_dir, cwd);
                has_prev = 1;
                continue;
            }
            if (strcmp(args[1], "-") == 0) {
                if (!has_prev) {
                    printf("%s\n", cwd);
                    continue;
                }
                if (chdir(prev_dir) != 0) {
                    perror("cd");
                    continue;
                }
                char new_cwd[LINE_SIZE];
                if (getcwd(new_cwd, sizeof(new_cwd)) == NULL) {
                    new_cwd[0] = '\0';
                }
                printf("%s\n", new_cwd);
                strcpy(prev_dir, cwd);
                continue;
            }
            if (chdir(args[1]) != 0) {
                perror("cd");
                continue;
            }
            strcpy(prev_dir, cwd);
            has_prev = 1;
            continue;
        }

        if (strcmp(args[0], "history") == 0) {
            if (n == 1) {
                print_history(history_path);
            } else if (n == 2 && strcmp(args[1], "-c") == 0) {
                clear_history(history_path);
            } else {
                fprintf(stderr, "seash: Usage error\n");
            }
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            execvp(args[0], args);
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
        if (!background) {
            int status;
            if (waitpid(pid, &status, 0) < 0) {
                perror("waitpid");
            }
        }
    }

    if (batch) {
        fclose(input);
    }
    return 0;
}
