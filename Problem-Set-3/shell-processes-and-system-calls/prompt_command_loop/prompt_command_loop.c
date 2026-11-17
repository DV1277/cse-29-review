#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void prompt_command_loop(){
        char buffer[1001];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *start = buffer;

        while (*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n') {
            start++;
        }

        if (*start == '\0') {
            continue;
        }

        size_t len = strlen(start);
        if (len > 0 && start[len - 1] == '\n') {
            start[len - 1] = '\0';
        }

        if (strcmp(start, "exit") == 0) {
            break;
        }

        char *end = start;
        while (*end != '\0' && *end != ' ' && *end != '\t' && *end != '\r' && *end != '\n') {
            end++;
        }

        *end = '\0';
        printf("%s\n", start);
    }
}

int main(int argc, char** argv) {
    prompt_command_loop();
    return 0;
}
