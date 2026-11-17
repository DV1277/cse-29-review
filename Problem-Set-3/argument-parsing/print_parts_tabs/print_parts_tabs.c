#include <stdio.h>
#include <string.h>

void print_parts_tabs(const char *str)
{
    if (str == NULL) {
        return;
    }

    char copy[1024];
    strcpy(copy, str);

    int index = 0;
    char* token = strtok(copy, "\t");

    while (token != NULL) {
        printf("%d: %s\n", index, token);
        index++;
        token = strtok(NULL, "\t");
    }
}

int main()
{
    char buffer[1001];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // Remove trailing newline if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        print_parts_tabs(buffer);
    }

    return 0;
}
