#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int binsearch( int *arr, int target, int size );

int main( void ) {
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int index;
	int size = 11;

	index = binsearch( arr, 11, size );
	fprintf( stdout, "%d\n", index );
	return 0;
}

int binsearch( int *arr, int target, int size ) {
	int l, r, m;
	int unsuccessful = -1;

	for ( l = 0, r = size - 1 ; l <= r; m = ( l + r ) / 2 ) {
		if ( arr[m] < target ) {
			l = m + 1;
		}
		else if ( arr[m] > target ) { 
			r = m - 1;
		}
		else{
			return m;
		}
	}
	return unsuccessful;
}
