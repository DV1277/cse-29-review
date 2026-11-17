#include <stdio.h>
#include <stdint.h>

// Given a 32-bit integer, return the number of 0 bits
// For example:
// Input -> Output
// 128 -> 31  (has one 1 bit, so thirty-one 0 bits)
// -1 -> 0    (all bits are 1, so zero 0 bits)
// 0 -> 32    (all bits are 0)
// 2147483647 -> 1 (all bits except the sign bit are 1)

int count_0_bits(int32_t n) {
    int32_t count = 0; 
    for (int i = 0; i < 32; i++){
        int bit = (n >> i) & 1;
        if (bit == 0){
            count++;
        }
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
            printf("%d\n", count_0_bits(number));
        }
    }
    
    return 0;
}
