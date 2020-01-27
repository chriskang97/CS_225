#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std ;

#include "DFS.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */

double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */ // Make another constructor that takes in DFS or BFS object.

}




ImageTraversal::Iterator::Iterator( PNG pic_, Point start_, double tol_, ImageTraversal* trav_, int type_  )
{
    pic = pic_ ;
    start = start_ ;
    tol = tol_ ;
    trav = trav_ ;
    type = type_ ;

    for( unsigned i = 0 ; i < pic.width() * pic.height() ; i++ )
    {
      visited.push_back(false) ;
    }

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point point ;

  unsigned temp_x ;
  unsigned temp_y ;

  if ( start.x != pic.width() && start.y != pic.height() )
  {
    point = trav->pop() ;
    visited[point.x + pic.width() * point.y ] = true  ;

    // 1) Right 2) Down 3) Left 4) Up
    for ( int i = 0 ; i < 4 ; i++ )
    {
      temp_x = point.x ;
      temp_y = point.y ;

      if ( i == 0 )
        temp_x = point.x + 1 ;

      else if ( i == 1 )
        temp_y = point.y + 1 ;

      else if ( i == 2 )
        temp_x = point.x - 1 ;

      else
        temp_y = point.y - 1 ;

        // Checking Boundary, Tolerance Condition, and Whether Coordinate has been visited.
        if ( temp_x < pic.width() && temp_y < pic.height() )
          if( calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(temp_x, temp_y) ) < tol )
            if ( visited[temp_x + pic.width() * temp_y] == false )
            {
              // For a Queue: If the Coordinate is in a Queue, ignore the current coordinate added
              // Otherwise if it's a stack, replace the coordinate into the stack.
              if ( type == 0 )
                trav->add(Point(temp_x, temp_y) ) ;

              else
              {
                visited[temp_x + pic.width() * temp_y] = true ;
                trav->add(Point(temp_x, temp_y) ) ;
              }

            }
    }
  }

  // Finally, for a stack if there are any leftovers repeated ones, get rid of them
  while ( !trav->empty() && type == 0 )
  {
    if ( visited[ trav->peek().x + pic.width() * trav->peek().y] == true )
      trav->pop() ;
    else
      break ;
  }

  if ( trav->empty() )
    start = Point(pic.width(),pic.height() ) ;

  return *this ;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return trav->peek()  ;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if ( this->start == other.start )
    return false ;

  return true ;
}

void ImageTraversal::Iterator::printing()
{
  cout<<"\n"<<endl ;
  for( unsigned i = 0 ; i < visited.size() ; i++ )
    cout<<visited[i]<<endl ;

}
