#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>

unsigned char * urlencode( unsigned char const *str );

int main( void ) {
	unsigned char url[0xFF] = "http://example.com.test/user?uid=1wha-tis that man_";
	unsigned char *encoded;

	encoded = urlencode( url );
	fprintf( stdout, "%s\n", encoded );
	return 0;
}

unsigned char * urlencode( unsigned char const *str ) {
	int i, j, k;
	size_t len;
	unsigned char *c;
	static unsigned char *encoded;
	char chars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	
	i = j = 0;
	len = strlen( str );
	encoded = (unsigned char *) malloc( (len * 3) + 1 );
	
	while ( str[i] != '\x00' ) {
		if ( str[i] == ' ' ) {
			encoded[j++] = '+';
		}
		else if ( (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= '0' && str[i] <= '9') ||
			 str[i] == '.' || str[i] == '~'  ||  str[i] == '-' || str[i] == '_' ) {
			encoded[j++] = str[i];
		} 
		else{
			encoded[j++] = '%';
			encoded[j++] = toupper( chars[ str[i] >> 4 ] );
			encoded[j++] = toupper( chars[ str[i] & 15 ] );
		}
		i++;
	}
	encoded[j] = '\x00';
	return encoded;
}
