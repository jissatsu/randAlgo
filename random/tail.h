#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAXLINE 1000
#define MAXLINES 100

int __getline( char *, int );
void __writelines( char **, int, int );
void _xfree_l( char **, int );