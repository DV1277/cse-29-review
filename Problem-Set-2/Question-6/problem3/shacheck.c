#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

// TODO: Implement this function
// Takes a string and an expected hash (as hex string)
// Computes SHA256 of the string, compares with expected hash
// Returns 1 if they match, 0 if they don't match
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
        char buffer[200];

        while (1)
        {
                char *maybe_eof = fgets(buffer, sizeof(buffer), stdin);
                if (maybe_eof == NULL)
                {
                        break;
                }

                // Remove newline if present
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len - 1] == '\n')
                {
                        buffer[len - 1] = '\0';
                }

                // Parse the line - find the first space
                char *space_pos = strchr(buffer, ' ');
                if (space_pos == NULL)
                {
                        continue; // Skip malformed lines
                }

                // Split into string and expected hash
                *space_pos = '\0';
                char *input = buffer;
                char *expected_hash = space_pos + 1;

                if (check_sha256(input, expected_hash)) {
            printf("match\n");
        } else {
            printf("miss\n");
        } 
        }

        return 0;
}
