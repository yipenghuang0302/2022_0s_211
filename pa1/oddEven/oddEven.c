#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  int number = atoi( argv[1] );
  printf ( number%2 ? "odd" : "even" );

  return EXIT_SUCCESS;
}
