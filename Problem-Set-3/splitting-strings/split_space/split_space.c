#include <stdio.h>
#include <string.h>

char* split_space(char* s){
    for (int i = 0; s[i] != '\0'; i++){ 
        if (s[i] == ' '){
            s[i] = '\0'; 
            return &s[i+1];
        }
    } 
    return s;
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

        char* string2 = split_space(buffer);
        printf("Original string: %s\n", buffer);
        printf("Split string: %s\n", string2);
    }
}
