#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

size_t mmap_write( void *addr, void *buff, size_t size ) {
    if( size <= 0 || buff == NULL )
        return 0;

    size_t written = 0;
    char *c;
    for( c = addr ; size > 0 ; size--, c++ ) {
        *c = *(char *)buff++;
        written++;
    }
    *c = '\x00';
    return written;
}

size_t mmap_read( void *addr, void *buff, size_t size ) {
    if( size <= 0 || buff == NULL )
        return 0;
        
    size_t read = 0;
    char *c;
    for( c = addr ; size > 0 ; size--, c++ ) {
        *(char *)buff++ = *c;
        read++;
    }
    *(char *)buff = '\x00';
    return read;
}

int main( int argc, char **argv ) {
    void *addr = mmap( NULL, 10, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS, -1, 0 );
    if( addr == MAP_FAILED ) {
        return -1;
    }
    char *str = "what?";
    size_t written = mmap_write( addr, str, strlen(str) + 1 );
    if( written == 0 ) {
        printf( "mmap_write() failed!\n" );
    }

    char out[10] = {0};
    size_t read = mmap_read( addr, out, written );
    if( read == 0 ) {
        printf( "mmap_read() failed!\n" );
    }
    printf( "%s\n", (char *) out );
    munmap( addr, 10 );
    return 0;
}