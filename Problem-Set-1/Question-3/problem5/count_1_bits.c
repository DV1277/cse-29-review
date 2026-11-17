#include <stdio.h>
#include <stdint.h>

// Given a 32-bit integer, return the number of 1 bits (aka the popcount/hamming weight) only using bitwise operators
// For example:
// Input -> Output


int count_1_bits(int32_t n) {
    uint32_t un = n;
    int count = 0;
    for (int i = 0; i < 32; i++){
        count =  count + (un & 1);
        un = un >> 1;
    }
    return count;
}

int main() {
    char line[20];  // Large enough for int32_t max value (2147483647) plus newline
    
    // Read lines until EOF
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int32_t number;
        if (sscanf(line, "%d", &number) == 1) {
            // Convert number and print result
            printf("%d\n", count_1_bits(number));
        }
    }
    
    return 0;
}
