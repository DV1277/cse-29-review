#include <stdio.h>
#include <string.h>

char* extract_second(char* s){
    char* first = strtok(s, " ");
    if (first != NULL) { 
        char* second = strtok(NULL, " ");
        if (second != NULL) {
            return second;
        }
    }

    return "No second string";
}


int main(int argc, char** argv) {
    char buffer[100];
    while(1) {
        char* maybe_eof = fgets(buffer, sizeof(buffer), stdin);
        if(maybe_eof == NULL) { break; }

        // Remove newline if present
        size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }

        printf("%s\n", extract_second(buffer));
    }
}
