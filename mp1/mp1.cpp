#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>

#include <iostream>
using namespace std;


void rotate(std::string inputFile, std::string outputFile)
{
  // TODO: Part 2

  PNG image1 ;

  image1.readFromFile( inputFile ) ;
  PNG image2( image1.width(), image1.height() ) ;

  for ( unsigned x = 0; x < image1.width(); x++ )
  {
    for ( unsigned y = 0; y < image1.height(); y++ )
    {
        // X_New = Max_X_Length - 1 - Current_X
        // Y_New = Max_Y_Length - 1 - Current_Y

        unsigned image1_x = image1.width() - 1 - x ;
        unsigned image1_y = image1.height() - 1 - y ;

        image2.getPixel(x,y) = image1.getPixel(image1_x, image1_y) ;
    }
  }

  image2.writeToFile(outputFile);


}

PNG myArt(unsigned int width, unsigned int height)
{
  PNG png(width, height);
  // TODO: Part 3

  double test_hue = 196  ;
  double test_sat = 1 ;
  double test_lum = 0.5 ;
  double test_lum_circle = 0.5 ;
  double test_lum_bg = 0.2 ;

  double add_lum_circle = 0.01 ;
  double add_lum_bg = 0.01 ;

  for ( unsigned x = 0; x < png.width(); x++ )
  {
    for ( unsigned y = 0; y < png.height(); y++ )
    {
          // test_hue = test_hue  ;
          // test_sat = test_sat + add_sat ;
          // test_lum = test_lum + add_lum ;

          double x_squared = (x-400) * (x-400) ;
          double y_squared = (y-400) * (y-400) ;
          double added_x_y = x_squared + y_squared ;

          double x_squared_2 = (x-400) * (x-400) ;
          double y_squared_2 = (y-300) * (y-300) ;
          double added_x_y_2 = x_squared_2 + y_squared_2 ;

          double x_squared_3 = (x-444) * (x-444) ;
          double y_squared_3 = (y-580) * (y-580) ;
          double added_x_y_3 = x_squared_3 + y_squared_3 ;

          if (test_hue == 196 )
          {
              test_hue = test_hue + 5 ;
          }

          else

          {
              test_hue = 196 ;
          }

          test_lum_circle = test_lum_circle + add_lum_circle ;

          if (test_lum_circle >= 0.8 )
          {
            add_lum_circle = -0.05 ;
          }

          if ( test_lum_circle <= 0.3 )
          {
            add_lum_circle = 0.05 ;
          }





          test_lum_bg = test_lum_bg + add_lum_bg ;

          if (test_lum_bg >= 0.3 )
          {
            add_lum_bg = -0.06 ;
          }

          if ( test_lum_bg <= 0.1 )
          {
            add_lum_bg = 0.06 ;
          }

          if ( 160000 >= added_x_y  && 120000 <=  added_x_y )
          {
              png.getPixel(x,y).h = test_hue ;
              png.getPixel(x,y).s = test_sat ;
              png.getPixel(x,y).l = test_lum_circle ;
              // cout << y << endl;
          }

          else

          {
              png.getPixel(x,y).h = 196 ;
              png.getPixel(x,y).s = 0.5 ;
              png.getPixel(x,y).l = test_lum_bg ;
          }


          // Making the 9 Sprite

          if ( 20000 >= added_x_y_2  && 15000 <= added_x_y_2 )
          {
              png.getPixel(x,y).h = test_hue ;
              png.getPixel(x,y).s = test_sat ;
              png.getPixel(x,y).l = test_lum ;
          }

          if ( x >= 523 && x <= 542 && y >= 300 && y <= 600 )
          {
              png.getPixel(x,y).h = test_hue ;
              png.getPixel(x,y).s = test_sat ;
              png.getPixel(x,y).l = test_lum ;
          }

          if ( 10000 >= added_x_y_3  && 6500 <= added_x_y_3 && y >= 600 && x >= 444 )
          {
              png.getPixel(x,y).h = test_hue ;
              png.getPixel(x,y).s = test_sat ;
              png.getPixel(x,y).l = test_lum ;
          }

          if ( x >= 383 && x <= 444 && y >= 661 && y <= 679  )
          {
              png.getPixel(x,y).h = test_hue ;
              png.getPixel(x,y).s = test_sat ;
              png.getPixel(x,y).l = test_lum ;

          }




    }
  }

  return png;
}
