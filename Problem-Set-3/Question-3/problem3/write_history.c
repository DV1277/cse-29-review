#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_history(const char *filepath, const char *command)
{
    FILE *file = fopen(filepath, "a");
    if (file == NULL)
    {
        perror("open");
        return -1;
    }
    fprintf(file, "%s\n", command);
    fclose(file);
    return 0;
}

int main()
{
    char buffer[1001];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        char *colon = strchr(buffer, ':');
        if (colon == NULL) continue;
        *colon = '\0';
        char *filepath = buffer;
        char *command = colon + 1;
        int result = write_history(filepath, command);
        if (result == 0) printf("success\n");
    }
    return 0;
}
