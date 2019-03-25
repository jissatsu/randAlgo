#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort( int *arr, size_t size );

int main( void ) {
	int arr[] = {5, 1, 4, 2, 6, 3, 7};
	
	bubble_sort( arr, 7 );
	for ( int i = 0 ; i < 7 ; i++ ) {
		fprintf( stdout, "%d\n", arr[i] );
	}
	return 0;
}

void bubble_sort( int *arr, size_t size ) {
	int i;
	int temp;
	int cicles;
	cicles = size;

	while ( cicles ) {
		for ( i = 0 ; i < (size - 1) ; i++ ) {
			if ( arr[i] > arr[i + 1] ) {
				temp       = arr[i];
				arr[i]     = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
		cicles--;
	}
}
