// Compile: g++ -Wall -std=c++11 box_blur_convolution.cpp -o blur -L/usr/X11R6/lib -lm -lpthread -lX11
// run    : ./blur /path/to/image

#include <iostream>
#include <vector>
#include "CImg-2.8.2/CImg.h"

using namespace std;
using namespace cimg_library;

#define PIX(x,y,z,c) *image->data( x, y, z, c )

template <class T>
T img( CImg<T> *image, int x, int y, int channel )
{
    T pix = ( x < 0 || y < 0 ) ? 0 : PIX( x, y, 0, channel ) ;
    return pix;
}

template <class T>
/*
 * get a 3x3 region from image (for specified channel)
 */
vector< vector<T> > region5x5( CImg<T> *image, int x, int y, int channel )
{
    vector<vector<T> > region(5, vector<T>(5, 0));

    for ( short i = -2, j = 0 ; i <= 2 ; i++, j++ ) {
        region[j][0] = img( image, x+(-2), y+i, channel );
        region[j][1] = img( image, x+(-1), y+i, channel );
        region[j][2] = img( image, x+( 0), y+i, channel );
        region[j][3] = img( image, x+( 1), y+i, channel );
        region[j][4] = img( image, x+( 2), y+i, channel );
    }
    return region;
}

template <class T>
/*
 * perform convolution and return new value for current pixel
 */
T convolution( char kernel[5][5], vector< vector<T> > region )
{
    vector< vector<T> > ac_matrix(5, vector<T>(5, 0));
    unsigned int pixval = 0;
    
    for ( short i = 0 ; i < 5 ; i++ ) {
        pixval += (kernel[i][0] * region[i][0]) + (kernel[i][1] * region[i][1]) +\
                  (kernel[i][2] * region[i][2]) + (kernel[i][3] * region[i][3]) +\
                  (kernel[i][4] * region[i][4]);
    }
    return pixval / 25;
}

template <class T>
short identity_img( CImg<T> *image )
{
    vector< vector<T> > region;
    T pix;
    char identity_matrix[5][5] = {
        { 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1 }
    };

    CImg<T> *img_copy = new CImg<T>( image->width(), image->height(), 1, 3 );
    img_copy->fill( 0.00 );
    
    for ( int x = 0 ; x < image->width() ; x++ ) {
        for ( int y = 0 ; y < image->height() ; y++ ) {
            for ( short i = 0 ; i < 3 ; i++ ) {
                region  = region5x5( image, x, y, i );
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
