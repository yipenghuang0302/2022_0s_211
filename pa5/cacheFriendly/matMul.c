#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define BLOCK 256

void matMulIJK (
    size_t m,
    size_t n,
    size_t p,
    int** a,
    int** b,
    int** c
) {
    for ( int i=0; i<m; i++ )
        for ( int j=0; j<p; j++ ) {
            int sum = 0;
            for ( int k=0; k<n; k++ )
                sum += a[i][k] * b[k][j];
            c[i][j] += sum;
        }

    return;
}
// JIK

void matMulKIJ (
    size_t m,
    size_t n,
    size_t p,
    int** a,
    int** b,
    int** c
) {
    for ( int k=0; k<n; k++ )
        for ( int i=0; i<m; i++ ) {
            int r = a[i][k];
            for ( int j=0; j<p; j++ )
                c[i][j] += r * b[k][j];
        }

    return;
}
// IKJ

void matMulJKI (
    size_t m,
    size_t n,
    size_t p,
    int** a,
    int** b,
    int** c
) {
    for ( int j=0; j<p; j++ )
        for ( int k=0; k<n; k++ ) {
            int r = b[k][j];
            for ( int i=0; i<m; i++ )
                c[i][j] += a[i][k] * r;
        }

    return;
}
// KJI

int main() {

    time_t t;
    srand((unsigned) time(&t));

    int m = rand() % 2048; // index by i
    int n = rand() % 2048; // index by k
    int p = rand() % 2048; // index by j
    m = 1024;
    n = 1024;
    p = 1024;

    // ALLOCATE AND INITIALIZE ARRAYS WITH RANDOM NUMBERS
    int** a = calloc( m, sizeof(int*) );
    for ( int i=0; i<m; i++ ) {
        a[i] = calloc( n, sizeof(int) );
        for ( int k=0; k<n; k++ )
            a[i][k] = rand() % 256;
    }

    int** b = calloc( n, sizeof(int*) );
    for ( int k=0; k<n; k++ ) {
        b[k] = calloc( p, sizeof(int) );
        for ( int j=0; j<p; j++ )
            b[k][j] = rand() % 256;
    }

    clock_t start, end;
    double cpu_time_used;

    // TIME matMulIJK
    int** ijkResult = calloc( m, sizeof(int*) );
    for ( int i=0; i<m; i++ )
        ijkResult[i] = calloc( p, sizeof(int) );

    start = clock();
    matMulIJK( m, n, p, a, b, ijkResult );
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("matMulIJK took %lf seconds.\n", cpu_time_used);

    // TIME matMulKIJ
    int** kijResult = calloc( m, sizeof(int*) );
    for ( int i=0; i<m; i++ )
        kijResult[i] = calloc( p, sizeof(int) );

    start = clock();
    matMulKIJ( m, n, p, a, b, kijResult );
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("matMulKIJ took %lf seconds.\n", cpu_time_used);

    // TIME matMulJKI
    int** jkiResult = calloc( m, sizeof(int*) );
    for ( int i=0; i<m; i++ )
        jkiResult[i] = calloc( p, sizeof(int) );

    start = clock();
    matMulJKI( m, n, p, a, b, jkiResult );
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("matMulJKI took %lf seconds.\n", cpu_time_used);

    // // TIME matMulRcrs
    // int** rcrResult = calloc( m, sizeof(int*) );
    // for ( int i=0; i<m; i++ )
    //     rcrResult[i] = calloc( p, sizeof(int) );
    //
    // start = clock();
    // matMulRCR( m, 0, n, 0, p, 0, a, b, rcrResult );
    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("matMulRCR took %lf seconds.\n", cpu_time_used);

    for ( int i=0; i<m; i++ )
        for ( int j=0; j<p; j++ ) {
            assert ( ijkResult[i][j] == kijResult[i][j] );
            assert ( kijResult[i][j] == jkiResult[i][j] );
        }

    for ( int i=0; i<m; i++ )
        free( jkiResult[i] );
    free(jkiResult);

    for ( int i=0; i<m; i++ )
        free( kijResult[i] );
    free(kijResult);

    for ( int i=0; i<m; i++ )
        free( ijkResult[i] );
    free(ijkResult);

    for ( int k=0; k<n; k++ )
        free( b[k] );
    free(b);

    for ( int i=0; i<m; i++ )
        free( a[i] );
    free(a);

    return EXIT_SUCCESS;
}
