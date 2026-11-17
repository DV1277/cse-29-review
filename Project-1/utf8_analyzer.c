#include <string.h>
#include <stdint.h>
#include <stdio.h>

int8_t is_ascii(char string[]){
    for(int i = 0; string[i] != '\0'; i++){
        if ((unsigned char)string[i] > 127){
            return 0;
        }
    }
    return 1;
}

int32_t capitalize_ascii(char str[])
{
    if (str == NULL){
        return 0;
    }
    
    int count = 0;

    for (int i = 0; str[i] != 0; i++){
        if (str[i] >= 'a' && str[i] <= 'z'){
            str[i] = str[i] - 32;
            count++;
        }
    }
    return count;
}

int8_t codepoint_size(char string[]) {
    if (string == NULL || string[0] == '\0'){
        return 0;
    }

    if ((string[0] & 0x80) == 0x00){
        return 1;
    }

    if ((string[0] & 0xE0) == 0xC0){
        return 2;
    }

    if ((string[0] & 0xF0) == 0xE0){
        return 3;
    }

    if ((string[0] & 0xF8) == 0xF0){
        return 4;
    }


    return -1;
}

int32_t utf8_strlen(char str[]) {
    for (int j = 0; str[j] != '\0'; ){
        char byte[] = {str[j], '\0'};
        int size = codepoint_size(byte);
        if (size == -1){
            return -1;
        }
        for (int k = 1; k < size; k++){
            if ((str[j + k] & 0xC0) != 0x80){
                return -1;
            }
        }
        j += size;
    }

    int32_t count = 0;
    int i = 0;
    while (str[i] != '\0'){
       if ((str[i] & 0xC0) != 0x80){
          count++;
       }
       i++;
    }
    return count;
}

void utf8_substring(const char str[], int start, int end, char result[]) {
    int count = 0;
    int copied = 0;

    if (start < 0 || start >= end){
        result[0] = '\0';
        return;
    }

    for (int i = 0; str[i] != '\0'; i++){
        if ((str[i] & 0xC0) != 0x80){
            count++;
        }

        if (count > start && count <= end){
            result[copied++] = str[i];
        }
    }

    result[copied] = '\0';
}

int32_t codepoint_at(char str[], int32_t byte_index) {
    int length = strlen(str);
    if (byte_index < 0 || byte_index >= length){
        return -1;
    }
    unsigned char b0 = str[byte_index];

    if ((b0 & 0x80) == 0x00){
        return b0;
    }

    if ((b0 & 0xE0) == 0xC0){
        unsigned char b1 = str[byte_index + 1];
        return ((b0 & 0x1F) << 6) | (b1 & 0x3F);
    }

    if ((b0 & 0xF0) == 0xE0){
        unsigned char b1 = str[byte_index + 1];
        unsigned char b2 = str[byte_index + 2];
        return ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
    }

    if ((b0 & 0xF8) == 0xF0){
        unsigned char b1 = str[byte_index + 1];
        unsigned char b2 = str[byte_index + 2];
        unsigned char b3 = str[byte_index + 3];
        return ((b0 & 0x07) << 18) | ((b1 & 0x3F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
    }

    return -1;
}

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

    if (str[i] == '\0' || str[i + 1] == '\0' || str[i + 2] == '\0' || str[i + 3] == '\0'){
        return 0;
    }

    unsigned char b0 = str[i];
    unsigned char b1 = str[i + 1];
    unsigned char b2 = str[i + 2];
    unsigned char b3 = str[i + 3];

    if (b0 == 0xF0 && b1 == 0x9F && b2 == 0x90 && b3 >= 0x80 && b3 <= 0xBF){
        return 1;
    }

    if (b0 == 0xF0 && b1 == 0x9F && b2 == 0xA6 && b3 >= 0x80 && b3 <= 0xAE){
        return 1;
    }

    return 0;
}

int main() {
    char str[2048], upper[2048], result[2048];

    printf("Enter a UTF-8 encoded string: ");
    if (fgets(str, sizeof(str), stdin) == NULL){
        return 0;
    }
    str[strcspn(str, "\n")] = '\0';

    printf("Valid ASCII: %s\n", is_ascii(str) ? "true" : "false");
    strcpy(upper, str);
    capitalize_ascii(upper);
    printf("Uppercased ASCII: \"%s\"\n", upper);
    printf("Length in bytes: %zu\n", strlen(str));
    printf("Number of code points: %d\n", utf8_strlen(str));

    printf("Bytes per code point:");
    for (int i = 0; str[i] != '\0'; i++){
        if ((str[i] & 0xC0) != 0x80){
            char byte[] = {str[i], '\0'};
            printf(" %d", codepoint_size(byte));
        }
    }
    printf("\n");

    utf8_substring(str, 0, 6, result);
    printf("Substring of the first 6 code points: \"%s\"\n", result);

    printf("Code points as decimal numbers:");
    for (int i = 0; str[i] != '\0'; i++){
        if ((str[i] & 0xC0) != 0x80){
            printf(" %d", codepoint_at(str, i));
        }
    }
    printf("\n");

    printf("Animal emojis: ");
    for (int i = 0; i < utf8_strlen(str); i++){
        if (is_animal_emoji_at(str, i)){
            utf8_substring(str, i, i + 1, result);
            printf("%s", result);
        }
    }
    printf("\n");
    return 0;
}
