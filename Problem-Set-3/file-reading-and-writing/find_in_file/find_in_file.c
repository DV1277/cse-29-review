#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint8_t find_in_file(char* path, char* to_find) {
    if (path == NULL || to_find == NULL){
        return 0;
    } 
    if (to_find[0] == '\0'){
        return 1;
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return 0;
    }

    char file_buffer[1024];
    uint8_t found = 0;
 
    while (fgets(file_buffer, sizeof(file_buffer), file) != NULL) {
        if (strstr(file_buffer, to_find) != NULL) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
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

        char* space = strchr(buffer, ' ');
        *space = '\0';
        char* path = buffer;
        char* to_find = space + 1;

        printf("%d\n", find_in_file(path, to_find));
    }
}
