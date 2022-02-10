#include <stdlib.h>
#include <stdio.h>

int main () {

    int* pointer0 = malloc(sizeof(int));
    printf("*pointer0 = %d\n", *pointer0);

    *pointer0 = 100;
    printf("*pointer0 = %d\n", *pointer0);

    free(pointer0);
    pointer0 = NULL;

    *pointer0 = 10;
    printf("*pointer0 = %d\n", *pointer0);

}
