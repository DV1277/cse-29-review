#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 2048  // Maximum length of input string in bytes

// Given a char[] representing a UTF-8 encoded string,
// return the number of UTF-8 codepoints (characters) in the string.
// The input will always be valid UTF-8 and will not exceed 2048 bytes.
int32_t utf8_strlen(char str[]) {
    int32_t count = 0;
    int i = 0;
    while (str[i] != '\0'){
       if ((str[i] & 0xC0) != 0x80){
          count++;
       }
       i++;
    }
    return count;
}

int main() {
    char input[MAX_LENGTH];  // Buffer for input string (max 2048 bytes)
    
    while (fgets(input, sizeof(input), stdin)) {
        // Remove trailing newline if present
        char* newline = strchr(input, '\n');
        if (newline) *newline = '\0';
        
        // Get and print the string length
        int32_t result = utf8_strlen(input);
        printf("%d\n", result);
    }
    
    return 0;
}
