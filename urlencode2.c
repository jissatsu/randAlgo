#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char * dec2hex( int num );
unsigned char * strrev( unsigned char const *str );
unsigned char * urlencode( unsigned char const *url );
void freeString( void *str );

int main( void ) {
	unsigned char url[0xFF] = "http://example.com.test/user?uid=1wha-tis that man_";
	unsigned char *encoded;
	
	encoded = urlencode( url );
	fprintf( stdout, "%s\n", encoded );
	freeString( encoded );
	return 0;
}

unsigned char * urlencode( unsigned char const *url ) {
	int i, j, len;
	static unsigned char *encoded;
	unsigned char *hex;
	char chars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	i = j = 0;
	len     = strlen( url );
	encoded = (unsigned char *) malloc( (len * 3) + 1 );

	while ( url[i] != '\x00' ) {
		if ( url[i] == ' ' ) {
			encoded[j++] = '+';
		}
		else if ( (url[i] >= 'A' && url[i] <= 'Z') || (url[i] >= 'a' && url[i] <= 'z') || 
				  (url[i] >= '0' && url[i] <= '9') ||
				  url[i] == '.' || url[i] == '-' || url[i] == '_' || url[i] == '~') {
			encoded[j++] = url[i];
		}
		else{
			encoded[j++] = '%';
			hex = dec2hex((int) url[i]);
			strcat( encoded, hex );
			j = j + 2;
		}
		i++;
	}
	encoded[j] = '\x00';
	return encoded;
}

unsigned char * dec2hex( int num ) {
	int i;
	int dec;
	int remainder;
	static unsigned char hex_str[0xFF];
	
	i = 0;
	dec = num;
	while ( dec ) {
		remainder = dec % 16;
		if ( remainder >= 0 && remainder <= 9 ) {
			hex_str[i++] = remainder + '0';
		} else{
			hex_str[i++] = remainder + 55;
		}
		dec = dec / 16;
	}
	hex_str[i] = '\x00';
	return strrev( hex_str );
}

unsigned char * strrev( unsigned char const *str ) {
	int i, j;
	int len;
	static unsigned char *newStr;
	
	len    = strlen( str );
	newStr = (unsigned char *) malloc( (len * sizeof( char )) + 1 );
	
	for ( i = (len - 1), j = 0 ; i >= 0 ; i--, j++ ) {
		newStr[j] = str[i];
	}
	newStr[j] = '\x00';
	return newStr;
}

void freeString( void *str ){
	free( str );
}
