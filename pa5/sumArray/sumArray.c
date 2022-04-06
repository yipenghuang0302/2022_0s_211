#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define M 1024

int sumArrayRows (
    int a[M][M]
) {
    int sum = 0;

    for ( int i=0; i<M; i++ )
        for ( int j=0; j<M; j++ ) {
            // printf( "a[i][j]=%d\n", a[i][j] );
            sum += a[i][j];
        }

    // printf( "sumArrayRows sum=%d\n", sum );
    return sum;
}

int sumArrayCols (
    int a[M][M]
) {
    int sum = 0;

    for ( int j=0; j<M; j++ )
        for ( int i=0; i<M; i++ )
            sum += a[i][j];

    // printf( "sumArrayCols sum=%d\n", sum );
    return sum;
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

int main() {

    time_t t;
    srand((unsigned) time(&t));

    int a[M][M];

    // INITIALIZE ARRAY WITH RANDOM NUMBERS
    for ( int j=0; j<M; j++ )
        for ( int i=0; i<M; i++ )
            a[i][j] = rand() % 256;

    clock_t start, end;
    double cpu_time_used;

    // TIME sumArrayRcrs
    // start = clock();
    // int sumArrayRcrsResult = sumArrayRcrs( M, 0, 0, a );
    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("sumArrayRcrs took %lf seconds.\n", cpu_time_used);


    // assert ( sumArrayRcrsResult == sumArrayRowsResult );

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





    // assert ( sumArrayRcrsResult == sumArrayColsResult );
    assert ( sumArrayRowsResult == sumArrayColsResult );

    return EXIT_SUCCESS;
}
