#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"
#include "colorPicker/MyColorPicker.h"
using namespace std;

int main()
{
    PNG border ;
    border.readFromFile("border.png");

    SquareMaze maze ;
    maze.makeMaze(border.width(), border.height() ) ;

    PNG* result = maze.drawMaze() ;
    result = maze.drawMazeWithSolution() ;

    for ( unsigned int x = 0 ; x < border.width() ; x++ )
      for ( unsigned int y = 0 ; y < border.height() ; y++ )
        if ( border.getPixel(x,y).h > 50 )
        {
          border.getPixel(x,y).h = result->getPixel(x,y).h ;
          border.getPixel(x,y).s = result->getPixel(x,y).s ;
          border.getPixel(x,y).l = result->getPixel(x,y).l ;

          if ( result->getPixel(x,y).l == 0 )
            border.getPixel(x,y).l = 0 ;
        }




    border.writeToFile("creative.png") ;
    return 0;
}
