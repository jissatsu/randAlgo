#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void freeString( void *str );
unsigned char * gen_random( size_t len );

int main( void ) {
	unsigned char *randStr;

	srand( ( unsigned ) time( NULL ) );
	randStr = gen_random( 100 );

	fprintf( stdout, "%s\n", randStr );
	freeString( randStr );
	return 0;
}

unsigned char * gen_random( size_t len ) {
	int i;
	char c;
	char chars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static unsigned char err[] = "Error";
	static unsigned char *randStr;
	size_t chars_len = strlen( chars );

	if ( len ) {
		randStr = (unsigned char *) malloc( (len * sizeof( char )) + 1 );
		if ( randStr ) {
			for ( i = 0 ; i < len ; i++ ) {
				c = chars[ rand() % chars_len ];
				randStr[i] = c;
			}
			randStr[i] = '\x00';
			return randStr;
		}
		return err;
	}
	return err;
}

void freeString( void *str ) {
	free( str );
}
