#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t is_ascii(char string[]){
    for(int i = 0; string[i] != '\0'; i++){
        if ((unsigned char)string[i] > 127){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    char buffer[100];
    uint8_t result;
    while (1)
    {
        char *maybe_eof = fgets(buffer, 99, stdin);
        if (maybe_eof == NULL)
        {
            break;
        }
        result = is_ascii(buffer);
        printf("%d\n", result);
    }
}
