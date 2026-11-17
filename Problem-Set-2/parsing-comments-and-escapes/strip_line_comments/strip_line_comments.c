#include <stdio.h>
#include <string.h>

void strip_line_comments(char str[])
{
   for (int i = 0; str[i] != '\0' && str[i + 1] != '\0'; i++) {
        if (str[i] == '/' && str[i + 1] == '/') {
            str[i] = '\0';
            break;       
        }
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

        strip_line_comments(buffer);
        printf("%s\n", buffer);
    }

    return 0;
}
