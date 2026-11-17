#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_parts(const char* str) { 
    int i = 0;
    int index = 0;
    while (str[i] != '\0') {
        while (str[i] == ' ' && str[i] != '\0') {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }
        printf("%d: ", index); 
        while (str[i] != ' ' && str[i] != '\0') {
           printf("%c", str[i]); 
            i++; 
        }
        printf("\n");
        index++;
    }
}

int main(int argc, char** argv) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Remove newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
        print_parts(buffer);
    }
}
