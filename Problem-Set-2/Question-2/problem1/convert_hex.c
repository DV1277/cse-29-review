#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// TODO: Implement this function
// Converts an 8-character hexadecimal string to a 32-bit unsigned integer
// Example: "deadbeef" returns 3735928559
uint32_t hex_to_uint(char *hex_string)
{
   	int32_t total;
    int32_t value;	
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
    return total; 
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

        // TODO: Remove newline if present
        uint32_t result = hex_to_uint(buffer);
        printf("%u\n", result);
    }

    return 0;
}
