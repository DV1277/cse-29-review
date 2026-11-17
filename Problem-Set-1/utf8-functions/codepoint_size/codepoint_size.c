#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Returns 1, 2, 3, or 4 depending on the size of the first codepoint in the string.
// Returns 0 if the string is empty
// Returns -1 if the first byte is not a valid UTF-8 start byte
int8_t codepoint_size(char string[]) {
    if (string == NULL || string[0] == '\0'){
        return 0;
    }

    if ((string[0] & 0x80) == 0x00){
        return 1;
    }

    if ((string[0] & 0xE0) == 0xC0){
        return 2;
    }

    if ((string[0] & 0xF0) == 0xE0){
        return 3;
    }

    if ((string[0] & 0xF8) == 0xF0){
        return 4;
    }


    return -1;
}
int main(int argc, char** argv) {
        char buffer[100];
        int8_t result;
        while(1) {
                char* maybe_eof = fgets(buffer, 99, stdin);
                if(maybe_eof == NULL) { break; }
                result = codepoint_size(buffer);
                printf("%d\n", result);
        }
}
