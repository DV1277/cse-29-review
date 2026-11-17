#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int32_t get_line(char* path, int line_number, char result[], int max) {
    if (path == NULL || result == NULL || line_number < 1 || max <= 0) {
        return -1;
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return -1;
    }

    char dummy_buffer[1024];
    
    for (int i = 1; i < line_number; i++) {
        if (fgets(dummy_buffer, sizeof(dummy_buffer), file) == NULL) {
            fclose(file);
            return -1;
        }
        
        while (dummy_buffer[strlen(dummy_buffer) - 1] != '\n') {
            if (fgets(dummy_buffer, sizeof(dummy_buffer), file) == NULL) {
                fclose(file);
                return -1;
            }
        }
    }

    if (fgets(dummy_buffer, sizeof(dummy_buffer), file) == NULL) {
        fclose(file);
        return -1;
    }

    int32_t bytes_to_copy = strlen(dummy_buffer);
    if (bytes_to_copy > max) {
        bytes_to_copy = max;
    }

    strncpy(result, dummy_buffer, bytes_to_copy);
    result[bytes_to_copy] = '\0';

    fclose(file);
    return bytes_to_copy;
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

        char* space1 = strchr(buffer, ' ');
        *space1 = '\0';
        char* path = buffer; // getting file path

        char* rest = space1 + 1;
        char* space2 = strchr(rest, ' ');
        *space2 = '\0';
        char* num1_str = rest; // getting len
        char* num2_str = space2 + 1; // getting max

        int num1 = atoi(num1_str); // convert len to number
        int num2 = atoi(num2_str); // convert max to number

        char result[num2 + 1];

        int32_t ret_num = get_line(path, num1, result, num2);
        if(ret_num == -1){printf("-1\n");}
        else{
            if (ret_num > 0 && result[ret_num - 1] == '\n') {
                result[ret_num - 1] = '\0';
            }
            printf("%d %s\n", ret_num, result);}
    }
}
