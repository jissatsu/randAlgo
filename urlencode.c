#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void freeString( void *str );
unsigned char * urlencode( unsigned char const *url, size_t len );

int main( int argc, char **argv ) {
	unsigned char url[] = "http://example.com.test/user?uid=1wha-tis that space_";
	unsigned char *encoded;
	
	encoded = urlencode( url, strlen( url )	);
	fprintf( stdout, "%s\n", encoded );
	freeString( encoded );
	
	return 0;
}

unsigned char * urlencode( unsigned char const *url, size_t len ) {
	int i;
	size_t actual_len   = strlen( url );
	unsigned char *encoded;
	char chars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	if ( len > 0 && len == actual_len ) {
		encoded = (unsigned char *) malloc( (len * 3) + 1 );
		if ( encoded ) {
			i = 0;
			while ( *url != '\x00' ) {
				if ( *url == ' ' ) {
					encoded[i++] = '+';
				} 
				else if ( (*url >= 'a' && *url <= 'z') || (*url >= 'A' && *url <= 'Z') || (*url >= '0' && *url <= '9') ||
					*url == '~' || *url == '.' || *url == '-' || *url == '_') {
					encoded[i++] = *url;
				} else{
					encoded[i++] = '%';
					encoded[i++] = toupper( chars[ *url >> 4 ] );
					encoded[i++] = toupper( chars[ *url & 15 ] );
				}
				url++;
			}
			encoded[i] = '\x00';
			return encoded;
		}
		return (unsigned char *) "[Error] - Couldn't allocate memory for encoded string!\n";
	}
	return (unsigned char *) "[Error] - The length provided is not the same as of the url!\n";
}

void freeString( void *str ) {
	free( str );
}
