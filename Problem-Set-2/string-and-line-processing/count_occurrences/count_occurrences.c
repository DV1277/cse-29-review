#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Returns the number of times the to_count character appears in str
int count_occurrences(const char* str, char to_count) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == to_count){
            count++;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    char buffer[1024];
    char to_count;
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Remove newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
        to_count = buffer[len-2]; 
        char* cptr = strrchr(buffer, ' ');
        int result;
        if (!cptr || *(cptr+1) == '\0') {
            to_count = '\0';
        } else {
            to_count = *(cptr+1);
            *cptr = '\0';
        }
        result = count_occurrences(buffer, to_count);
        printf("%d\n", result);
    }
}

