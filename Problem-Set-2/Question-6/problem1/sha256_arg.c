#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main(int argc, char **argv)
{
    // TODO: Read string from argv[1] and print its SHA256 hash
    // as a 64-character lowercase hexadecimal string
    if (argc < 2) {
        return 1;
    }

    char *my_string = argv[1];

    size_t len = strlen(my_string);
    if (len > 0 && my_string[len - 1] == '\n') {
        my_string[len - 1] = '\0';
    }

    unsigned char hash[32];  
    
    SHA256((unsigned char*)my_string, strlen(my_string), hash);

    for(int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
