#include <stdio.h>
#include <string.h>
#include <stdint.h>

// TODO: Implement this function
// Returns 1 if the string is a palindrome (reads the same forwards
// and backwards), 0 otherwise.
uint8_t is_palindrome(char str[])
{
    int left = 0;
    int right = strlen(str) - 1;
    
  
    while (left < right) {
        if (str[left] != str[right]) {
            return 0; 
        }
        left++;
        right--;
    }

    return 1;
}

int main()
{
        // TODO: Read strings from stdin in a loop (one per line)
        // Call is_palindrome on each input
        // Print 1 or 0 for each result
    char buffer[1024];
  
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    { 
        buffer[strcspn(buffer, "\r\n")] = '\0';

        uint8_t result = is_palindrome(buffer);
     
        printf("%u\n", result);
    }

    return 0; 
}
