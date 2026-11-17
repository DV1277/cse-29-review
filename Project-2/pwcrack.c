#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <openssl/sha.h>

int check_sha256(char *input_string, char *expected_hash)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char computed_hex[SHA256_DIGEST_LENGTH * 2 + 1];

    SHA256((unsigned char*)input_string, strlen(input_string), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&computed_hex[i * 2], "%02x", hash[i]);
    }
    computed_hex[SHA256_DIGEST_LENGTH * 2] = '\0';

    if (strcmp(computed_hex, expected_hash) == 0) {
        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <hash>\n", argv[0]);
        return 1;
    }

    char *target_hash = argv[1];
    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        if (check_sha256(line, target_hash)) {
            printf("Found password: SHA256(%s) = %s\n", line, target_hash);
            found = 1;
            break;
        }

        int i = 0;
        while (line[i] != '\0' && !found)
        {
            char original = line[i];

            if (original >= 'a' && original <= 'z') {
                line[i] = original - 32; 
            } else if (original >= 'A' && original <= 'Z') {
                line[i] = original + 32; 
            } else {
                i++;
                continue; 
            }

            if (check_sha256(line, target_hash)) {
                printf("Found password: SHA256(%s) = %s\n", line, target_hash);
                found = 1;
            }

            line[i] = original; 
            i++;
        }

        if (found) {
            break;
        }
    }

    if (!found) {
        printf("Did not find a matching password\n");
    }

    return 0;
}