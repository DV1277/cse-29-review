#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// TODO: Implement this function
// Converts an 8-character hexadecimal string to 4 bytes
// Prints each byte as a decimal number separated by spaces
// Example: "deadbeef" prints "222 173 190 239"
void hex_to_bytes(char *hex_string)
{
    int32_t value = 0;
    int32_t total = 0;
    for (int i = 0; hex_string[i] != '\0'; i++){
        char c = hex_string[i]; 
        if (c >= '0' && c <= '9'){
            value = c - '0';
        }
        else if (c >= 'a' && c <= 'f'){
            value = (c - 'a') + 10;
        }
        else if (c >= 'A' && c <= 'F'){
            value = (c - 'A') + 10;
        }
        else{
            break;
        }
        total = (total << 4) | value;        
    }
    uint32_t byte1 = (total >> 24) & 0xFF;
    uint32_t byte2 = (total >> 16) & 0xFF;
    uint32_t byte3 = (total >> 8) & 0xFF;
    uint32_t byte4 = (total) & 0xFF;

    printf("%d %d %d %d\n", byte1, byte2, byte3, byte4);
}

int main(int argc, char **argv)
{
        char buffer[100];

        while (1)
        {
                char *maybe_eof = fgets(buffer, sizeof(buffer), stdin);
                if (maybe_eof == NULL)
                {
                        break;
                }

        hex_to_bytes(buffer);


                
        }

        return 0;
}
