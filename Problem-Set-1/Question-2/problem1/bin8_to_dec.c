#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Given a char[8] representing a binary number, returns the signed 8-bit integer it represents
// For example:
//   "10000000" produces -128 (most negative 8-bit number)
//   "00000001" produces 1
//   "00000000" produces 0
//   "11111111" produces -1
//   "01111111" produces 127 (most positive 8-bit number)

int8_t bin8_to_dec(char binary[]) {
    int8_t decimal = 0;
   for(int i = 0; i < 8; i++){
     int bit = binary[i] - '0';
     decimal = (decimal << 1) | bit ;   
    }
	return decimal;
}

int main() {
    char line[10];  // Extra space for newline and null terminator
    
    // Read lines until EOF
    while (fgets(line, sizeof(line), stdin) != NULL) {
        // Remove newline if present
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Convert binary string to decimal and print
        printf("%d\n", bin8_to_dec(line));
    }
    
    return 0;
}
