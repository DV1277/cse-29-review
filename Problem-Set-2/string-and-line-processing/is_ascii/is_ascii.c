#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int is_ascii(char* str) {
    while (*str) {
        if ((unsigned char)*str > 127) {
            return 0;
        }
        str++;
    }
    return 1;
}

int main(int argc, char** argv) {
   if (argc < 2) 
    {
        return 1; 
    }

    int result = is_ascii(argv[1]);

    printf("%d\n", result);

    return 0; 
}
