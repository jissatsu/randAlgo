#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char * strrev( unsigned char const *str );

int main( void ) {
	unsigned char str[] = "Hello World!";
	unsigned char *reversed;

	reversed = strrev( str );
	fprintf( stdout, "%s\n", reversed );
	return 0;
}

unsigned char * strrev( unsigned char const *str ) {
	int i, j;
	size_t len;
	unsigned char *newStr;
	
	len = strlen( str );
	newStr = (unsigned char *) malloc( len * sizeof( char ) );

	for ( i = (len - 1), j = 0 ; i >= 0 ; i--, j++ ) {
		newStr[j] = str[i];
	}
	newStr[j] = '\x00';
	return newStr;
}
