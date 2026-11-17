#include <stdlib.h>
#include <stdio.h>

void definitely_lost() {
    int* p = malloc(sizeof(int));
}

void indirectly_lost() {
    int** pp = malloc(sizeof(int*));
    *pp = malloc(sizeof(int));
}

int* array;
void possibly_lost() {
    array = malloc(sizeof(int) * 5);
    array += 2;
}

int* global_p;
void still_reachable() {
    global_p = malloc(sizeof(int));
}

int main() {
    definitely_lost();
    indirectly_lost();
    possibly_lost();
    still_reachable();
    return 0;
}
