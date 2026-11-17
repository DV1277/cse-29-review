#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Given a 32-bit unsigned integer x and an unsigned 8-bit integer n,
// return an unsigned 32-bit integer containing just the least n significant bits of x.
// If n is greater than or equal to 32, return x unchanged.
// If n is 0, return 0.
uint32_t lowest_n(uint32_t x, uint8_t n) {
    if (n >= 32){
        return x;
    }
    if (n == 0){
        return 0;
    }
    uint32_t mask = (1u << n) - 1;
    return x & mask;
}

int main() {
    char input[20];  // Large enough for 0x + 8 hex digits + space + 2 decimal digits + newline
    uint32_t x;
    uint8_t n;
    
    while (fgets(input, sizeof(input), stdin)) {
        // Parse hex number and decimal n from input
        if (sscanf(input, "%x %hhu", &x, &n) == 2) {
            uint32_t result = lowest_n(x, n);
            printf("0x%08x\n", result);
        }
    }
    
    return 0;
}
