#include <stdio.h>
#include <stdint.h>

// Given a int8_t, return 1 if the number is even or 0 if the number is odd only using bitwise operators
// For example:
// Input -> Output
// 0 -> 1
// 1 -> 0
// -2 -> 1
// 29 -> 0

int bitwise_is_even(int8_t n) {
    return (n & 1) ^ 1;
}

int main() {
    char line[6];  // Sufficient for int8_t + newline + null terminator
    
    // Read lines until EOF
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int8_t number;
        if (sscanf(line, "%hhd", &number) == 1) {
            // Convert number and print result
            printf("%d\n", bitwise_is_even(number));
        }
    }
    
    return 0;
}
