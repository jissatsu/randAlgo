#include <stdio.h>

// convert fahrenheit to celsius 
float fahr2cel( float fahr )
{
    float celsius = (fahr - 32) * 5 / 9;
    return celsius;
}

// convert celsius to fahrenheit
float cel2fahr( float celsius )
{
    float fahr = ((celsius * 9) / 5) + 32;
    return fahr;
}

int main( int argc, char **argv )
{
    printf( "%.2f\n", fahr2cel( 68.00 ) );
    printf( "%.2f\n", cel2fahr( 20.00 ) );
    return 0;
}