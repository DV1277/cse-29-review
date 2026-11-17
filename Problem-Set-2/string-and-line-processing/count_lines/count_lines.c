#include <stdio.h>
#include <string.h>

int main() {
    // TODO: Read lines from stdin until EOF
    // Count the total number of lines
    // Print the count as a single number
    
    char buffer[100];
    int count = 0;
    while(fgets(buffer, sizeof(buffer), stdin) != NULL) { 
        count++; 
    }    
    printf("%d", count);
    return 0;
}
