#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    // TODO: Parse command-line flags
    // -d <delim> : custom delimiter (default: " ")
    // -s <sep> : custom separator (default: "\n")

    char *delim = " "; // default delimiter
    char *sep = "\n";  // default separator

    // Parse flags from argv
    // Hint: loop through argv, check for "-d" and "-s"
    // When you find a flag, the next argument is its value
    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0 && i + 1 < argc)
        {
            delim = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc)
        {
            sep = argv[i + 1];
            i++;
        }
    }

    char buffer[1001];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // Remove trailing newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        // Tokenize by delim and print with sep
        // TODO: Implement this
        
        int first = 1;
        char *token = strtok(buffer, delim);
        while (token != NULL)
        {
            if (!first)
            {
                printf("%s", sep);
            }
            printf("%s", token);
            first = 0;
            token = strtok(NULL, delim);
        }
        printf("\n");

    }

    return 0;
}
