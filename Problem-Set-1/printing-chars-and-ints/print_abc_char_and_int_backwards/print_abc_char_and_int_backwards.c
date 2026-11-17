#include <stdio.h>
#include <string.h>

void print_abc_char_and_int_backwards(char str[]) {
    int len = strlen(str); 
    for (int i = len-1; i>=0; i--){
        printf("%c %u\n", str[i], str[i]);
    }
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

        print_abc_char_and_int_backwards(buffer);
    }
}
