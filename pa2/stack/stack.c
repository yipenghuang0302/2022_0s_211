#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct element {
    int number;
    struct element* next;
};

// Append the new element to the start of the stack
// show what happens on the stack and on the heap
struct element* stack = NULL;

void push (
    int number
) {}

// Remove element from the top of the stack
int pop () {}

int main(int argc, char* argv[])
{

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }


    char buff[5];
    while ( fscanf(fp, "%s", buff) != -1 ) {

        if ( strcmp(buff,"PUSH")==0 ) {
            unsigned int number;
            fscanf(fp, "%d", &number);
            push(number);
        } else if ( strcmp(buff,"POP")==0 ) {
            pop(); // discard the return
        } else {
            printf("UNEXPECTED INPUT\n");
            return EXIT_FAILURE;
        }
    }

    while (stack) {
        int data = pop();
        printf( "%d\n", data );
    }

    fclose(fp);
    return 0;
}
