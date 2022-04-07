#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define M 4

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Markers used to bound trace regions of interest */
volatile char MARKER_START, MARKER_END;

int sumArrayRows (
    int a[M][M]
) {
    int sum = 0;

    MARKER_START = 211;
    for ( int i=0; i<M; i++ )
        for ( int j=0; j<M; j++ ) {
            // printf( "a[i][j]=%d\n", a[i][j] );
            sum += a[i][j];
        }
    MARKER_END = 211;

    // printf( "sumArrayRows sum=%d\n", sum );
    return sum;
}

int sumArrayCols (
    int a[M][M]
) {
    int sum = 0;

    MARKER_START = 211;
    for ( int j=0; j<M; j++ )
        for ( int i=0; i<M; i++ )
            sum += a[i][j];
    MARKER_END = 211;

    // printf( "sumArrayCols sum=%d\n", sum );
    return sum;
}

int main(int argc, char* argv[])
{

    // prepare random number generator
    time_t t;
    srand((unsigned) time(&t));

    // prepare timing infrastructure
    clock_t start, end;
    double cpu_time_used;

    /* Record marker addresses */
    FILE* marker_fp = fopen(".marker","w");
    assert(marker_fp);
    fprintf(marker_fp, "%llx\n%llx",
        (unsigned long long int) &MARKER_START,
        (unsigned long long int) &MARKER_END );
    fclose(marker_fp);

    int a[M][M];
    // INITIALIZE ARRAY WITH RANDOM NUMBERS
    for ( int j=0; j<M; j++ )
        for ( int i=0; i<M; i++ )
            a[i][j] = rand() % 256;

    // TIME sumArrayRows
    start = clock();
    int sumArrayRowsResult = sumArrayRows(a);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("sumArrayRows took %lf seconds.\n", cpu_time_used);

    // TIME sumArrayCols
    start = clock();
    int sumArrayColsResult = sumArrayCols(a);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("sumArrayCols took %lf seconds.\n", cpu_time_used);

    assert ( sumArrayRowsResult == sumArrayColsResult );

    // TIME sumArrayRcrs
    // start = clock();
    // int sumArrayRcrsResult = sumArrayRcrs( M, 0, 0, a );
    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("sumArrayRcrs took %lf seconds.\n", cpu_time_used);

    // assert ( sumArrayRcrsResult == sumArrayRowsResult );
    // assert ( sumArrayRcrsResult == sumArrayColsResult );

    exit(EXIT_SUCCESS);

}

// int sumArrayRcrs (
//     int size,
//     int row_offset,
//     int col_offset,
//     int a[M][M]
// ) {
//     if (size<2) {
//         int sum = 0;
//
//         for ( int j=0; j<size; j++ )
//             for ( int i=0; i<size; i++ )
//                 sum += a[row_offset+i][col_offset+j];
//
//         return sum;
//     } else {
//         int sum = 0;
//         sum += sumArrayRcrs( size>>1, row_offset+0        , col_offset+0        , a );
//         sum += sumArrayRcrs( size>>1, row_offset+0        , col_offset+(size>>1), a );
//         sum += sumArrayRcrs( size>>1, row_offset+(size>>1), col_offset+0        , a );
//         sum += sumArrayRcrs( size>>1, row_offset+(size>>1), col_offset+(size>>1), a );
//         // printf( "sum=%d\n", sum );
//         return sum;
//     }
// }
