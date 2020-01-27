#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;
using namespace std ;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(PNG & image )
{
    width = image.width() ;

    for( unsigned j = 0 ;  j < image.height() ; j ++ )
      for( unsigned i = 0; i < image.width() ; i++  )
      {
          image_ref.push_back(image.getPixel(i,j) ) ;
      }
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y ) {
  /* @todo [Part 3] */

  return image_ref[x + y * width ];
}
