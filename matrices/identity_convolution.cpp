// Compile: g++ -Wall -std=c++11 identity_convolution.cpp -o id -L/usr/X11R6/lib -lm -lpthread -lX11
// run    : ./id /path/to/image

#include <iostream>
#include <vector>
#include "CImg-2.8.2/CImg.h"

using namespace std;
using namespace cimg_library;

#define PIX(x,y,z,c) *image->data( x, y, z, c )

template <class T>
T img( CImg<T> *image, int x, int y, int channel )
{
    int w = image->width();
    int h = image->height();

    T pix = ( x < 0 || y < 0 ) ? 0 : PIX( x, y, 0, channel ) ;
    return pix;
}

template <class T>
/*
 * get a 3x3 region from image (for specified channel)
 */
vector< vector<T> > region3x3( CImg<T> *image, int x, int y, int channel )
{
    vector<vector<T> > region(3, vector<T>(3, 0));

    region[0][0] = img( image, x+(-1), y+(-1), channel );
    region[0][1] = img( image, x+( 0), y+(-1), channel );
    region[0][2] = img( image, x+( 1), y+(-1), channel );
    
    region[1][0] = img( image, x+(-1), y+( 0), channel );
    region[1][1] = img( image, x+( 0), y+( 0), channel );
    region[1][2] = img( image, x+( 1), y+( 0), channel );
    
    region[2][0] = img( image, x+(-1), y+( 1), channel );
    region[2][1] = img( image, x+( 0), y+( 1), channel );
    region[2][2] = img( image, x+( 1), y+( 1), channel );

    return region;
}

template <class T>
/*
 * perform convolution and return new value for current pixel
 */
T convolution( char kernel[3][3], vector< vector<T> > region )
{
    vector< vector<T> > ac_matrix(3, vector<T>(3, 0));
    unsigned char pixval = 0;
    
    for ( short j = 0 ; j < 3 ; j++ ) {
        ac_matrix[j][0] = kernel[j][0] * region[j][0];
        ac_matrix[j][1] = kernel[j][1] * region[j][1];
        ac_matrix[j][2] = kernel[j][2] * region[j][2];
    }
    for ( short i = 0 ; i < 3 ; i++ ) {
        pixval += (ac_matrix[i][0] + ac_matrix[i][1] + ac_matrix[i][2]);
    }
    return pixval;
}

template <class T>
short identity_img( CImg<T> *image )
{
    vector< vector<T> > region;
    T pix;
    char identity_matrix[3][3] = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 }
    };

    CImg<T> *img_copy = new CImg<T>( image->width(), image->height(), 1, 3 );
    img_copy->fill( 0.00 );
    
    for ( int x = 0 ; x < image->width() ; x++ ) {
        for ( int y = 0 ; y < image->height() ; y++ ) {
            for ( short i = 0 ; i < 3 ; i++ ) {
                region  = region3x3( image, x, y, i );
                pix     = convolution( identity_matrix, region );
                *img_copy->data( x, y, 0, i ) = pix;
            }
        }
    }
    img_copy->save( "identity.jpg" );
    delete img_copy;
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
        ? init_rgb_image( argv[1], img )
        : new CImg<double>( argv[1] );

    identity_img( image );
    delete image;
    //delete hgram;
    return 0;
}
