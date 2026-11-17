#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_history(const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        perror("open");
        return -1;
    }

    char line_buffer[1001];
    int line_number = 1;

    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL)
    {
        printf("%d %s", line_number, line_buffer);
        line_number++;
    }

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
        read_history(buffer);
    }
    return 0;
}
