#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using namespace cs225;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {

  for ( unsigned x = 0; x < image.width(); x++ )
  {
    for ( unsigned y = 0; y < image.height(); y++ )
    {
      double x_length = abs(centerX - (int)x ) ;
      double y_length = abs(centerY - (int)y ) ;

      double distance = pow( pow(x_length,2) + pow(y_length,2), 0.5 ) ;

      if (distance >= 160)
      {
        image.getPixel(x,y).l = 0.2 * image.getPixel(x,y).l ;
      }

      else
      {
        image.getPixel(x,y).l = ( 1 - 0.005 * distance) * image.getPixel(x,y).l ;
      }

    }
  }

  return image;

}


/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {

  for ( unsigned x = 0; x < image.width(); x++ )
  {
    for ( unsigned y = 0; y < image.height(); y++ )
    {
      // Obtain Current Hue Value
      double Current_Hue_Value = image.getPixel(x,y).h ;

      // Need to check the distance both counterclockwise and clockwise
      double orange_distance_1 = abs( Current_Hue_Value - 11 ) ;
      double orange_distance_2 = abs( 360 - Current_Hue_Value + 11 ) ;
      double blue_distance_1 = abs( Current_Hue_Value - 216 ) ;
      double blue_distance_2 = abs( 360 - Current_Hue_Value + 216 ) ;

      double least_orange_distance = 0 ;
      double least_blue_distance = 0 ;

      // Determine which of the distance is shortest
      if ( orange_distance_1 < orange_distance_2 )
      {
        least_orange_distance = orange_distance_1 ;
      }

      else

      {
        least_orange_distance = orange_distance_2 ;
      }

      if ( blue_distance_1 < blue_distance_2 )
      {
        least_blue_distance = blue_distance_1 ;
      }

      else

      {
        least_blue_distance = blue_distance_2 ;
      }

      // Determine which color to use. Whichever has least distance toward each color will be chosen.
      if ( least_orange_distance  < least_blue_distance  )
      {
        image.getPixel(x,y).h = 11 ;
      }

      else
      {
        image.getPixel(x,y).h = 216 ;
      }


    }
  }

  return image;
}


/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs to be averaged together.
* @param secondImage The second of the two PNGs to be averaged together.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {

  for ( unsigned x = 0; x < firstImage.width(); x++ )
  {
    for ( unsigned y = 0; y < firstImage.height(); y++ )
    {
        double second_pic_lum = secondImage.getPixel(x,y).l ;

        if ( second_pic_lum == 1.0 )
        {
          firstImage.getPixel(x,y).l = firstImage.getPixel(x,y).l + 0.2 ;
        }
    }
  }



  return firstImage;
}
