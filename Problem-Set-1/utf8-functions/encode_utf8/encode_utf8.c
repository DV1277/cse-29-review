#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void encode_utf8(uint32_t num, char dest[]) {
    if (num <= 0x7F) {
        dest[0] = (char)num;
    }

    else if (num <= 0x7FF) {
        dest[0] = (char)(0xC0 | ((num >> 6) & 0x1F));
        dest[1] = (char)(0x80 | (num & 0x3F));     
    }

    else if (num <= 0xFFFF) {
        dest[0] = (char)(0xE0 | ((num >> 12) & 0x0F));
        dest[1] = (char)(0x80 | ((num >> 6) & 0x3F));
        dest[2] = (char)(0x80 | (num & 0x3F));         
    }
 
    else if (num <= 0x10FFFF) {
        dest[0] = (char)(0xF0 | ((num >> 18) & 0x07)); 
        dest[1] = (char)(0x80 | ((num >> 12) & 0x3F)); 
        dest[2] = (char)(0x80 | ((num >> 6) & 0x3F));  
        dest[3] = (char)(0x80 | (num & 0x3F));         
    }
}


void print_array(char arr[]){
    for (int i = 0; i < 4; i++) {
        printf("%02X ", (unsigned char)arr[i]);
    }
    printf("\n");
}


int main(int argc, char** argv) {
        char buffer[100];
        char dest[4] = {0};
        while(1) {
                char* maybe_eof = fgets(buffer, sizeof(buffer), stdin);
                if(maybe_eof == NULL) { break; }
                uint32_t num = (uint32_t)strtoul(buffer, NULL, 10); // Convert input string to number
                for (int i = 0; i < 4; i++) dest[i] = 0; //Reset dest to be all 0
                encode_utf8(num, dest);
                print_array(dest);
        }
}
