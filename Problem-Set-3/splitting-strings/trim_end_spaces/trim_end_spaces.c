#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Given a char* that may have trailing spaces, change the string to have a null terminator where the first space in the list of trailing spaces starts.
void trim_end_spaces(char* str) {
    int i;
    int last_word_end = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            last_word_end = i + 1;
        }
    }
    str[last_word_end] = '\0';
}    

int main(int argc, char** argv) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Remove newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
        trim_end_spaces(buffer);
        printf("%s\n", buffer);
    }
}
