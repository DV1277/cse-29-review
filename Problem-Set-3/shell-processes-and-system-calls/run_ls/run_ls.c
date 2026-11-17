#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run_ls(const char str[]){
    pid_t pid = fork();

    if (pid < 0) {
        return -1;
    }
    else if (pid == 0) {
        execlp("ls", "ls", str, NULL);
        perror("exec failed");
        exit(1);
    }
    else {
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}

int main(int argc, char** argv) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
        run_ls(buffer);
    }
    return 0;
}
