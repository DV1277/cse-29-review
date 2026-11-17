#include <stdio.h>
#include <stdint.h>

// Given a uint32_t, returns the most significant (leftmost) 16 bits as a uint16_t
// For example:
//   0xFFFFFFFF -> 0xFFFF (65535)
//   0x00000000 -> 0x0000 (0)
//   0x00010000 -> 0x0001 (1)
//   0x80000000 -> 0x8000 (32768)
//   0xDEADBEEF -> 0xDEAD (57005)
uint16_t first_half(uint32_t number) {
    return number >> 16;
}

int main() {
    char line[20];  // Large enough for uint32_t max value (4294967295) plus newline
    
    // Read lines until EOF
    while (fgets(line, sizeof(line), stdin) != NULL) {
        uint32_t number;
        if (sscanf(line, "%u", &number) == 1) {
            // Convert number and print result
            printf("%u\n", first_half(number));
        }
    }
    
    return 0;
}
