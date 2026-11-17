#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Extracts the substring from codepoint index start (inclusive) to end (exclusive)
void utf8_substring(const char str[], int start, int end) {
        int count = 0;

    for (int i = 0; str[i] != '\0'; i++){
        if ((str[i] & 0xC0) != 0x80){
            count++;
        }

        if (count > start && count <= end){
            printf("%c", str[i]);
        }
    }

    printf("\n");
}

int main(int argc, char** argv) {
        char buffer[1024];
        int start, end;

        while (fgets(buffer, sizeof(buffer), stdin)) {
                // Remove newline
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';

                // Parse end from end
                char* endptr = strrchr(buffer, ' ');
                if (!endptr) continue;
                end = atoi(endptr + 1);
                *endptr = '\0';

                // Parse start
                char* startptr = strrchr(buffer, ' ');
                if (!startptr) continue;
                start = atoi(startptr + 1);
                *startptr = '\0';

                // buffer now holds the string
                utf8_substring(buffer, start, end);
        }
}
