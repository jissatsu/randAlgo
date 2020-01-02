#include <stdio.h>

int main( int argc, char **argv )
{
    short arr[10];
    short fibNum, n1, n2;

    n1 = 0;
    n2 = 1;

    for ( int i = 0 ; i < 10 ; i++ )
    {
        if ( i == 0 || i == 1 ) {
            arr[i] = i;
            continue;
        }

        fibNum = n2 + n1;
        n1     = n2;
        n2     = fibNum;
        arr[i] = fibNum;
    }

    for ( int i = 0 ; i < 10 ; i++ ) {
        printf( "%d\n", arr[i] );
    }
    return 0;
}
