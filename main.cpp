#include <iostream>
#include "CImg-2.8.2/CImg.h"

using namespace std;
using namespace cimg_library;

#define PIX(x,y,z,c) *image->data( x, y, z, c )

template <class T>
int grayscl_at_offset( CImg<T> *image, size_t offset )
{
    int x, y;
    if ( image == NULL ) {
        return -1;
    }

    T r, g, b;
    for ( x = offset ; x < image->width() ; x++ ) {
        for ( y = 0x00 ; y < image->height() ; y++ ) {
            r = (PIX( x, y, 0, 0x00 ) + PIX( x, y, 0, 0x01 ) + PIX( x, y, 0, 0x02 )) / 3.0;
            g = (PIX( x, y, 0, 0x00 ) + PIX( x, y, 0, 0x01 ) + PIX( x, y, 0, 0x02 )) / 3.0;
            b = (PIX( x, y, 0, 0x00 ) + PIX( x, y, 0, 0x01 ) + PIX( x, y, 0, 0x02 )) / 3.0;

            PIX( x, y, 0, 0x00 ) = r;
            PIX( x, y, 0, 0x01 ) = g;
            PIX( x, y, 0, 0x02 ) = b;
        }
    }
    return 0x00;
}

template <class T>
int sepia_tone_at_offset( CImg<T> *image, size_t offset ) {
    int x, y;
    if ( image == NULL ) {
        return -1;
    }
    T r, g, b;
    for ( x = offset ; x < image->width() ; x++ ) {
        for ( y = 0x00 ; y < image->height() ; y++ ) {
            r = (PIX( x, y, 0, 0x00 ) * .393) + (PIX( x, y, 0, 0x01 ) *.769) + (PIX( x, y, 0, 0x00 ) * .189);
            g = (PIX( x, y, 0, 0x00 ) * .349) + (PIX( x, y, 0, 0x01 ) *.686) + (PIX( x, y, 0, 0x00 ) * .168);
            b = (PIX( x, y, 0, 0x00 ) * .272) + (PIX( x, y, 0, 0x01 ) *.534) + (PIX( x, y, 0, 0x00 ) * .131);

            r = std::min( r, 255.0 );
            g = std::min( g, 255.0 );
            b = std::min( b, 255.0 );

            PIX( x, y, 0, 0x00 ) = r;
            PIX( x, y, 0, 0x01 ) = g;
            PIX( x, y, 0, 0x02 ) = b;
        }
    }
    return 0x00;
}

template <class T>
int adjust_brigthness( CImg<T> *image )
{
    int x, y;
    if ( image == NULL ) {
        return -1;
    }
    
    for ( x = 0 ; x < image->width() ; x++ ) {
        for ( y = 0 ; y < image->height() ; y++ ) {
            PIX( x, y, 0, 0x00 ) = min( PIX( x, y, 0, 0x00 ) + 40.0, 255.0 );
            PIX( x, y, 0, 0x01 ) = min( PIX( x, y, 0, 0x01 ) + 40.0, 255.0 );
            PIX( x, y, 0, 0x02 ) = min( PIX( x, y, 0, 0x02 ) + 40.0, 255.0 );
        }
    }
    return 0x00;
}

template <class T>
CImg<T> * init_rgb_image( const char *name, CImg<T> &img )
{
    if ( name == NULL ) {
        return NULL;
    }

    CImg<T> *image = new CImg<T>( img.width(), img.height(), 1, 3 );
    if ( image == NULL ) {
        return NULL;
    }
    std::memcpy( image->_data, img._data, img.size() * sizeof( T ) );

    for ( int x = 0 ; x < image->width() ; x++ ) {
        for ( int y = 0 ; y < image->height() ; y++ ) {
            PIX( x, y, 0, 0x01 ) = PIX( x, y, 0, 0x00 );
            PIX( x, y, 0, 0x02 ) = PIX( x, y, 0, 0x00 );
        }
    }
    return image;
}

int main( int argc, char **argv )
{
    if ( argc != 2 ) {
        puts( "Image path needed!\n" );
        exit( 1 );
    }

    if ( !argv[1] ) {
        puts( "Image path needed!\n" );
        exit( 1 );
    }
    
    CImg<double> img( argv[1] );

    CImg <double> *image = ( img.spectrum() == 0x01 )
        ? init_rgb_image(   argv[1], img )
        : new CImg<double>( argv[1] );

    grayscl_at_offset(    image, image->_width / 2 );
    sepia_tone_at_offset( image, image->_width / 2 );
    image->save( "nicenice3.jpg" );
    delete image;
    return 0;
}