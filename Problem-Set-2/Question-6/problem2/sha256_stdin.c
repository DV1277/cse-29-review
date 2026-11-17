#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main()
{
        // TODO: Implement a loop that reads lines from stdin until EOF.
        // For each line (up to 1000 characters):
        // 1. Remove trailing newline if present
        // 2. Compute SHA256 hash
        // 3. Print hash as lowercase hex (64 characters)
    char buffer[1001];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        unsigned char hash[32];
        SHA256((unsigned char*)buffer, strlen(buffer), hash);

        for (int i = 0; i < 32; i++) {
            printf("%02x", hash[i]);
        }
        printf("\n");
    }

    return 0;
}
