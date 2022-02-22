#include <stdlib.h>
#include <stdio.h>

int main () {

    printf("sizeof(char) = %ld byte\n", sizeof(char));
    for (size_t i=0; i<256; i++) {
        printf("(char) %ld = %c\n", i, (char) i);
    }

    return(EXIT_SUCCESS);
}
