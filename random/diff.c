#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>

#define MAXLINES 1000
#define MAXLEN   2000

struct files
{
    int nlines;
    char *name;
    char *lines[MAXLINES];
    FILE *fp;
} 
files[2];

int __fsize( FILE * );
int __getfiles( int, char **, struct files *, char * );
int __readlines( struct files * );
int __readfile( struct files *, int );
int __getline( char *, FILE *, int );
void __free_lines( struct files * );
void __fscompare( struct files * );


int main( int argc, char **argv )
{
    int nfiles = argc - 1;
    char *prg  = argv[0], err[70];

    if ( argc != 3 ) {
        fprintf( stderr, "%s: usage file1 file2\n", prg );
        return -1;
    }

    if ( __getfiles( nfiles, argv, files, err ) == -1 ){
        fprintf( stderr, "%s", err );
        return -1;
    }
    
    if ( __readlines( files ) == 0 ) {
        __fscompare( files );
        __free_lines( files );
    }
    return 0;
}

int __getfiles( int nfiles, char **argv, struct files *files, char *err )
{
    while ( nfiles-- > 0 )
    {
        files->fp = fopen( *++argv, "r" );
        if ( files->fp == NULL )
        {
            sprintf( err, "%s: %s\n", *argv, strerror( errno ) );
            return -1;
        }
        files->name = *argv, files++;
    }
    return 0;
}

int __readlines( struct files *files )
{
    while ( files->name != NULL )
    {
        __readfile( files, MAXLINES );
        files++;
    }
    return 0;
}

int __readfile( struct files *files, int max )
{
    int nlines;
    char line[MAXLEN];

    nlines = 0;
    while ( __getline( line, files->fp, MAXLEN ) > 0 )
    {
        files->lines[nlines] = (char *) malloc( MAXLEN );
        strcpy( files->lines[nlines++], line );
    }
    files->nlines = nlines;
    return 0;
}

void __fscompare( struct files *files )
{
    register int i;
    for ( i = 0 ; i < files[0].nlines ; i++ ){
        if ( strcmp( files[0].lines[i], files[1].lines[i] ) != 0 )
        {
            fprintf(
                stdout, "\n--%s--\n%s\n--%s--\n%s\n", 
                files[0].name, files[0].lines[i],
                files[1].name, files[1].lines[i] 
            );
            return;
        }
    }
}

int __getline( char *line, FILE *ifp, int max )
{
    register int c, i;

    i = 0;
    while ( --max > 0 && (c = getc( ifp )) != EOF && c != '\n' )
        *line++ = c, i++;
    if ( c == '\n' ){
        *line++ = c, i++;
    }
    *line = '\0';
    return i;
}

int __fsize( FILE *ifp )
{
    register int c, i;

    i = 0;
    while ( (c = getc( ifp )) != EOF ) {
        i++;
    }
    return i;
}

void __free_lines( struct files *files )
{
    while ( files->name != NULL ){
        for ( register int i = 0 ; i < files->nlines ; i++ )
        {
            free( files->lines[i] );
        }
        files++;
    }
}