#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
        // TODO: Read strings from stdin in a loop (one per line)
        // For each string, print all variants where exactly one
        // ASCII letter has its case flipped (upper->lower or lower->upper)
        // Each variant should be on its own line

     char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        for (int i = 0; buffer[i] != '\0'; i++)
        {
            char original = buffer[i];
            if (original >= 'A' && original <= 'Z')
            {
                buffer[i] = original + 32;
                printf("%s\n", buffer);
                buffer[i] = original; 
            }
            else if (original >= 'a' && original <= 'z')
            {
                buffer[i] = original - 32;
                printf("%s\n", buffer);
                buffer[i] = original;
            }
        }
    }

    return 0;
}
