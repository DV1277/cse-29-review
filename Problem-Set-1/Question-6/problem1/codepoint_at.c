#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int32_t codepoint_at(char str[], int32_t byte_index) {
    unsigned char b0 = str[byte_index];

    if ((b0 & 0x80) == 0x00){
        return b0;
    }

    if ((b0 & 0xE0) == 0xC0){
        unsigned char b1 = str[byte_index + 1];
        return ((b0 & 0x1F) << 6) | (b1 & 0x3F);
    }

    if ((b0 & 0xF0) == 0xE0){
        unsigned char b1 = str[byte_index + 1];
        unsigned char b2 = str[byte_index + 2];
        return ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
    }

    if ((b0 & 0xF8) == 0xF0){
        unsigned char b1 = str[byte_index + 1];
        unsigned char b2 = str[byte_index + 2];
        unsigned char b3 = str[byte_index + 3];
        return ((b0 & 0x07) << 18) | ((b1 & 0x3F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
    }

    return -1;
}

int main() {
    char input[2048];
    int32_t byte_index;
    
    // Read lines of input until EOF
    while (scanf("%[^\n]%*c", input) == 1) {
        // Get the byte index after the space
        char* space = strrchr(input, ' ');
        if (space != NULL) {
            *space = '\0';  // Split string at space
            byte_index = atoi(space + 1);
            
            // Call function and print result
            printf("%d\n", codepoint_at(input, byte_index));
        }
    }
    
    return 0;
}
