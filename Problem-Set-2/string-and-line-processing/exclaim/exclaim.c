#include <stdio.h>



int main()
{
    char buffer[21];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("%s!", buffer);
    }        
    
    return 0;
}
