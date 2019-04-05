#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int wcount( const char *str, size_t len );
int split_string( char *str, size_t len, char *delim, char **tokens, int *num_tokens, char *errbuf );

int main( int argc, char **argv ) {
	char word[]  = "    https://     ube.com/ tch?v=   OlDh2Rskfk8&lis  t=RDKZVvBhl3Pe0&index=9    ";
	char delim[] = " ";
	char errbuf[0xFF], *tokens[0xFF];
	int num_tokens, rcode;
	size_t len;

	len   = strlen( word );
	rcode = split_string( word, len, delim , tokens, &num_tokens, errbuf);
	
	if ( !rcode ) {
		for ( int i = 0 ; i < num_tokens ; i++ ) {
			fprintf( stdout, "%s\n", tokens[i] );
			free( tokens[i] );
		}
		return 0;
	}
	fprintf( stdout, "%s\n", errbuf );
	return 1;
}

int wcount( const char *str, size_t len ) {
	int i   = 0,
		j   = 0,
		k   = 0,
	in_word = 0;

	while ( isspace( str[i] ) ) { i++; }
	for ( j = i ; j < len ; j++ ) {
		if ( str[j] == ' ' || str[j] == '\t' || str[j] == '\n' ) {
			if ( in_word == 1 ) {
				in_word = 0;
			}
		} else {
			if ( in_word == 0 ) {
				in_word = 1, k++;
			}
		}
	}
	return k;
}

int split_string( char *str, size_t len, char *delim, char **tokens, int *num_tokens, char *errbuf ) {
	char *start, *copy;
	char *end = str + (len - 1);
	char *string;
	char word[0xFF];
	char err[] = "String is of length 0 or contains only whitespace.";
	int count = wcount( str, len );
	int indices[count], indices_size, i, j, k, found_delim = 0;

	copy = str;

	/* remove leading and trailing WSP and delimeters */
	while ( isspace( *str ) || *str == *delim )
		str++;
	start  = str;
	string = start;

	while ( isspace( *end ) || *end == *delim )
		end--;

	while ( string != (end + 1) ) {
		/* we found one and now we know that there is atleast one delimeter so no need to check any further */
		if ( *string == *delim ) {
			found_delim = 1; 
			break;
		}
		string++;
	}
	/* if none found copy the whole string */
	if ( found_delim == 0 ) {
		*num_tokens = 1;
		tokens[0]   = (char *) malloc( len * sizeof( char * ) );
		strcpy( tokens[0], copy ); return 0;
	}
	/**/

	string = start;
	found_delim = 0;
	if ( strlen( string ) > 0 ) {
		/* store every word's start index in an array */
		for ( i = 0, j = 0 ; string != (end + 1) ; i++ ) {
			if ( i == 0 ) {
				indices[j++] = i;
			} else {
				if ( *string == *delim ) {
					found_delim = 1;
				} else {
					if ( found_delim == 1 ) {
						found_delim = 0, indices[j++] = i;
					}
				}
			}
			string++;
		}

		string       = start;
		indices_size = j;
		/* if there are any indices stored in the array, proceed */
		if ( indices_size > 0 ) {
			for ( i = 0 ; i < indices_size ; i++ ) {
				k = 0;
				for ( j = indices[i] ; string[j] != *delim && &string[j] != (end + 1) ; j++ ) {
					word[k++] = string[j];
				}
				word[k]   = '\x00';
				tokens[i] = (char *) malloc( k * sizeof( char * ) );
				strcpy( tokens[i], word );
			}
			*num_tokens = indices_size;
			return 0;
		}
		strcpy( errbuf, err ), *num_tokens = 0; return EXIT_FAILURE;
	}
	strcpy( errbuf, err ), *num_tokens = 0; return EXIT_FAILURE;
}
