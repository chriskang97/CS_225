
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  Animation animation ;

  PNG image1 ;
  image1.readFromFile("image1.png") ;

  PNG image2 ;
  image2.readFromFile("image2.png") ;

  PNG image3 ;
  image3.readFromFile("image3.png") ;

  FloodFilledImage image (image1)  ;

  BFS bfs( image1, Point(165,120), 0.05 ) ;
  MyColorPicker color1 (image2 ) ;

  BFS bfs2( image1, Point(329,0), 0.05 ) ;
  MyColorPicker color2 (image3 ) ;

  image.addFloodFill(bfs, color1 ) ;
  image.addFloodFill(bfs2, color2) ;

  animation = image.animate(3000) ;


  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");





  return 0;
}
