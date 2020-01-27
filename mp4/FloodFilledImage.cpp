#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

#include <queue>

using namespace std ;
/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */

  base_image = png ;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */

  trav.push_back(&traversal) ;
  color_fill.push_back( &colorPicker) ;
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  int num_iter = trav.size() ;
  unsigned frame_num = 0 ;

  HSLAPixel frame ;

  animation.addFrame(base_image) ;

  for( int i = 0 ; i < num_iter ; i++  )
  {
    ImageTraversal* t = trav[i] ;

    for( const Point & p : *t )
    {
      frame = color_fill[i]->getColor( p.x, p.y ) ;
      HSLAPixel & base_image_pixel = base_image.getPixel( p.x, p.y ) ;

      base_image_pixel.h = frame.h ;
      base_image_pixel.s = frame.s ;
      base_image_pixel.l = frame.l ;
      base_image_pixel.a = frame.a ;

      frame_num += 1 ;

      if( frame_num%frameInterval == 0 )
        animation.addFrame(base_image) ;

    }

  }

  animation.addFrame(base_image) ;
  return animation;
}
