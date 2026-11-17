#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Implement the is_animal_emoji_at function here!
// Your function should match the following signature:
// It should return 1 if the codepoint at the given index is an animal emoji, 0 otherwise.
// You may add any helper functions you need.
int is_animal_emoji_at(const char str[], int index){
    int i = 0;
    int count = 0;

    while (str[i] != '\0'){
        unsigned char b = str[i];
        if ((b & 0xC0) != 0x80){
            if (count == index){
                break;
            }
            count++;
        }
        i++;
    }

    if (str[i] == '\0'){
        return 0;
    }

    unsigned char b0 = str[i];
    unsigned char b1 = str[i + 1];
    unsigned char b2 = str[i + 2];
    unsigned char b3 = str[i + 3];

    if (b0 == 0xF0 && b1 == 0x9F && b2 == 0x90){
        return 1;
    }

    if (b0 == 0xF0 && b1 == 0x9F && b2 == 0xA6 && b3 >= 0x80 && b3 <= 0xAE){
        return 1;
    }

    return 0;
}

int main(int argc, char** argv) {
    char buffer[1024];
    int idx;
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Remove newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
        // Parse index from end
        char* idxptr = strrchr(buffer, ' ');
        if (!idxptr) continue;
        idx = atoi(idxptr + 1);
        *idxptr = '\0';
        // buffer now holds the string
        int result = is_animal_emoji_at(buffer, idx);
        printf("%d\n", result);
    }
}
