#include <stdio.h>
#include <string.h>
#include <stdint.h>

void bin_to_dec_signed(char str[]) {
    int32_t decimal = 0;
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++){
        int bit = str[i] - '0';
        decimal = (decimal << 1) | bit;
        len++;
    }

    if (len > 0 && len < 32){
        decimal = (decimal << (32 - len)) >> (32 - len);
    }

    printf("%d\n", decimal);
}


int main(int argc, char** argv) {
    char buffer[100];
    while(1) {
        char* maybe_eof = fgets(buffer, sizeof(buffer), stdin);
        if(maybe_eof == NULL) { break; }
        
        // Remove newline if present
        size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }

        bin_to_dec_signed(buffer);
    }
}
