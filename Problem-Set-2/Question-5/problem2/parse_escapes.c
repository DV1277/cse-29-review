#include <stdio.h>
#include <string.h>

void parse_escapes(char str[])
{
    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (str[i] == '\\' && str[i + 1] != '\0') {
            char next = str[i + 1];

            if (next == 'n') {
                str[j++] = '\n';
                i += 2;
            } 
            else if (next == 't') {
                str[j++] = '\t';
                i += 2;
            } 
            else if (next == '\\') {
                str[j++] = '\\';
                i += 2;
            } 
            else if (next == '"') {
                str[j++] = '"';
                i += 2;
            } 
            else {
                str[j++] = str[i++];
            }
        } 
        else {
            str[j++] = str[i++];
        }
    }

    str[j] = '\0';
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

                parse_escapes(buffer);
                printf("%s\n", buffer);
        }

        return 0;
}
