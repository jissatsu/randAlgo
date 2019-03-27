#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strindexr( char *s, char *t );

int main( void ) {
	char str1[] = "tastes good the sandwich DO YOU know sandwich";
	char str2[] = "tastes good the sandwich DO YOU know sandwic";
	char pattern[] = "wich";
	
	fprintf( stdout, "String 1 -> %d\n", strindexr( str1, pattern ) );
	fprintf( stdout, "String 2 -> %d\n", strindexr( str2, pattern ) );
	return 0;
}

int strindexr( char *s, char *t ) {
	int i, j, k, found;
	
	for ( i = strlen( s ) - 1 ; i >= 0 ; i-- ) {
		for ( j = i , k = strlen( t ) - 1, found = strlen( t ) - 1 ; k > 0 && t[k] == s[j] ; j--, k--, found-- ) {
			;
		}
		if ( found == 0 ) {
			return i;
		}
	}
	return -1;
}
