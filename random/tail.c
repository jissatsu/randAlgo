#include "tail.h"

int main( int argc, char **argv )
{
    int len;
    int opt;
    int tail   = 0;
    int nlines = 0;
    char *lines[MAXLINES];
    char line[MAXLINE];
    
    while ( (opt = getopt( argc, argv, "n:" )) != -1 ) {
        switch ( opt ) {
            case 'n':
                tail = 1;
                break;
            default:
                fprintf( stdout, "Usage: %s -n {num}", argv[0] );
                exit( EXIT_FAILURE );
        }
    }
    
    // if option is ok start reading/storing lines
    if ( tail )
    {
        // set tail to the number of lines
        tail = optind;
        while ( (len = __getline( line, MAXLINE )) > 0 ) 
        {
            lines[nlines] = (char *) malloc( MAXLINE );
            strcpy( lines[nlines], line );
            nlines++;
    }
    __writelines( lines, nlines, tail ), _xfree_l( lines, nlines );
    }
    return 0;
}

/* __getline: read a line of input */
int __getline( char *line, int max )
{
    int c, i;
    
    i = 0;
    while ( --max > 0 && (c = getchar()) != EOF && c != '\n' ) {
        *line++ = c, ++i;
    }
    if ( c == '\n' ) {
        *line++ = c, ++i;
    }
    *line = '\x00';
    return i;
}

/* __writelines: write a bunch of lines to STDOUT */
void __writelines( char **lines, int nlines, int tailcount )
{
    int i, n;
    n = ( nlines >= tailcount ) ? tailcount : nlines ;
    
    for ( i = nlines - 1 ; --n >= 0 ; i-- ) {
        fprintf( stdout, "%s", lines[i] );
    }
}

/* _xfree_l: free the allocated lines */
void _xfree_l( char **lines, int max )
{
    int i;
    for ( i = 0 ; i < max ; i++ ) {
        free( lines[i] );
    }
}
