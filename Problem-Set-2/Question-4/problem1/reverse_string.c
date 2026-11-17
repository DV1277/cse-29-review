#include <stdio.h>
#include <string.h>

// TODO: Implement this function
// Reverses the string in-place by swapping characters from both ends
// moving toward the center.
void reverse_string(char str[])
{
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;

        left++;
        right--;
    }
}

int main()
{
    // TODO: Read strings from stdin in a loop (one per line)
    // Call reverse_string on each input
    // Print the reversed string
    char buffer[256];


    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {  

        reverse_string(buffer);

        printf("%s\n", buffer);
    }

    return 0;

}
