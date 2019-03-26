#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char * strrev1( unsigned char const *str );
unsigned char * strrev2( unsigned char *str );

int main( void ) {
	unsigned char str1[] = "Hello World!";
	unsigned char str2[] = "Hello World!";
	unsigned char *reversed;
	
	/* strrev1 */
	reversed = strrev1( str1 );
	fprintf( stdout, "%s\n", reversed );
	
	/* strrev2 */
	strrev2( str2 );
	fprintf( stdout, "%s\n", str2 );
	return 0;
}

unsigned char * strrev1( unsigned char const *str ) {
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

unsigned char * strrev2( unsigned char *str ){
	int i, j;
	unsigned char temp;

	for ( i = 0, j = strlen( str ) - 1 ; i < j ; i++, j-- ) {
		temp   = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}
