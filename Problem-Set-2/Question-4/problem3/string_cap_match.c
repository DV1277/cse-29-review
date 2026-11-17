#include <stdio.h>
#include <string.h>
#include <ctype.h>

// TODO: Implement this function
// Returns 1 if strings match or differ by exactly one capitalization change
// Returns 0 otherwise
// Examples:
//   "secret" and "seCret" -> 1 (one change)
//   "secret" and "seCreT" -> 0 (two changes)
//   "hello" and "hello" -> 1 (same)
int string_cap_match(char *s1, char *s2)
{
    int count = 0;
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {  
            if ((s1[i] - s2[i] == 32 || s2[i] - s1[i] == 32)) {
                count++;
            } else {
                return 0;
            }
        }
        i++;
    }

    
    if (s1[i] != '\0' || s2[i] != '\0') {
        return 0;
    }

    
    return (count == 0 || count == 1);
}

int main()
{
        // TODO: Read lines from stdin in a loop
        // Each line contains two strings separated by a space
        // Parse the two strings from each line
        // Call string_cap_match and print "match" or "miss"
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) 
    {
        char *s1 = strtok(buffer, " \t\r\n");
        char *s2 = strtok(NULL, " \t\r\n");

        if (s1 != NULL && s2 != NULL) {
            printf("%s\n", string_cap_match(s1, s2) ? "match" : "miss");
        }
    }

    return 0;
}
