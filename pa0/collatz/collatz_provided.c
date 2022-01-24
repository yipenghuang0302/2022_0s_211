#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  // Open the filename given as the first command line argument for reading
  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }

  char buf[256];
  char* string = fgets(buf, 256, fp);
  int number = ... ; // The starting number for the Collatz sequence

  /* ... */

  // Printing in C.
  // %d is the format specifier for integer numbers.
  // \n is the newline character
  printf( "%d\n", number );

  return EXIT_SUCCESS;
}
