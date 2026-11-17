#include <stdio.h>

// Given a char, returns 1 if it starts with the bits `10` and 0 if it does not
// For example:
//   0b10110101 -> 1 (starts with 10)
//   0b11000000 -> 0 (starts with 11)
//   0b01110000 -> 0 (starts with 01)
//   0b10000000 -> 1 (starts with 10)
//   0b00001111 -> 0 (starts with 00)
int starts_with_10(char c) {
    if ((c & 0xC0) == 0x80){
        return 1;
    }
    return 0;
}

int main() {
    char line[5];  // Large enough for char max value (255) plus newline
    
    // Read lines until EOF
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int number;
        if (sscanf(line, "%d", &number) == 1) {
            // Convert number and print result
            printf("%d\n", starts_with_10((char)number));
        }
    }
    
    return 0;
}
