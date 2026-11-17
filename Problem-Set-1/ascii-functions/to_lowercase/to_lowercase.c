#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t to_lowercase(char str[])
{
    if (str == NULL){
        return 0;
    }

    int count = 0;

    for (int i = 0; str[i] != 0; i++){
        if (str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
            count++;
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    char buffer[100];
    int32_t num_updated;
    while (1)
    {
        char *maybe_eof = fgets(buffer, 99, stdin);
        if (maybe_eof == NULL)
        {
            break;
        }
        num_updated = to_lowercase(buffer);
        printf("%d %s", num_updated, buffer);
    }
}
