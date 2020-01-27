/* Your code here! */

#include "maze.h"
#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"
#include <map>
#include <time.h>
#include <iostream>
#include <stack>
#include <unistd.h>

using namespace std ;
using namespace cs225 ;

SquareMaze::SquareMaze()
{
  srand( time(NULL) ) ;
}

bool SquareMaze::canTravel(int x, int y, int dir ) const
{
  int direction ;

  // 0 Means Right, 1 Means Down, 2 Means Left, 3 Means Up
  switch(dir)
  {
    case 0:
      direction = 1 ;
      break ;

    case 1 :
      direction = width_ ;
      break ;

    case 2:
      direction = -1 ;
      break ;

    case 3:
      direction = -width_ ;
      break ;
  }

  // Boundary Conditions for out of Bounds
  int tile_num = x + y * width_ + direction ;

  if ( ( tile_num < 0) || (tile_num >= height_ * width_) )
    return false ;

  // Checking Wall Condition for Right and Up
  auto specific_tile = tile.find( x + y * width_ ) ;

  if ( ( dir == 0 && specific_tile->second.first == 1) || (dir == 1 && specific_tile->second.second == 1) )
    return false ;

  // Checking Wall Condition for Left and Down
  specific_tile = tile.find( tile_num ) ;

  if ( (dir == 2 && specific_tile->second.first == 1) || (dir == 3 && specific_tile->second.second == 1) )
    return false ;

  // Checked Out of Bounds and Wall Condition thus tile is safe to move
  return true ;
}

PNG* SquareMaze::drawMaze() const
{
  PNG* draw_maze = new PNG( width_* 10 + 1, height_ * 10 + 1 ) ;

  // Unsure if Need to Add saturation etc
  for ( int x = 10 ; x < width_ * 10 + 1 ; x++ )
    draw_maze->getPixel(x,0).l = 0 ;

  for ( int y = 0 ; y < height_ * 10 + 1 ; y++ )
    draw_maze->getPixel(0,y).l = 0 ;

  // Coloring in the Walls
  for ( int x = 0 ; x < width_ ; x++ )
    for ( int y = 0 ; y < height_ ; y++ )
    {
      auto specific_tile = tile.find( x + y * width_ ) ;

      // Check Right Wall
      if ( specific_tile->second.first )
        for ( int k = 0 ; k <= 10 ; k++ )
          draw_maze->getPixel( (x+1)*10, y*10 + k).l = 0 ;

      // Check Bottom Wall
      if ( specific_tile->second.second )
        for ( int k = 0 ; k <= 10 ; k++ )
          draw_maze->getPixel( x*10 + k, (y+1)*10 ).l = 0 ;
    }

  return draw_maze ;
}

PNG* SquareMaze::drawMazeWithSolution()
{
  PNG* draw_maze = drawMaze() ;
  vector<int> solution = solveMaze() ;

  int start_x = 0 ;
  int start_y = 0 ;

  while ( !solution.empty() )
  {
    int dir = solution.at(0) ;
    int test = solution.size()  ;
    switch(dir)
    {
      case 0:
        for ( int x = 10 * (start_x) + 5 ; x <= 10 * (start_x + 1) + 5 ; x++ )
        {
          draw_maze->getPixel(x, start_y * 10 + 5).s = 1 ;
          draw_maze->getPixel(x, start_y * 10 + 5).l = 0.5 ;
        }

        start_x += 1 ;
        break ;

      case 1 :
        for ( int y = 10 * (start_y) + 5 ; y <= 10 * (start_y + 1) + 5 ; y++ )
        {
          draw_maze->getPixel(start_x * 10 + 5, y).s = 1 ;
          draw_maze->getPixel(start_x * 10 + 5, y).l = 0.5 ;
        }

        start_y += 1 ;
        break ;

      case 2:
        for ( int x = 10 * (start_x) + 5 ; x >= 10 * (start_x - 1) + 5; x-- )
        {
          draw_maze->getPixel(x, start_y * 10 + 5).s = 1 ;
          draw_maze->getPixel(x, start_y * 10 + 5).l = 0.5 ;
        }

        start_x -= 1 ;
        break ;

      case 3:
        for ( int y = 10 * (start_y) + 5; y >= 10 * (start_y - 1) + 5 ; y-- )
        {
          draw_maze->getPixel(start_x * 10 + 5, y).s = 1 ;
          draw_maze->getPixel(start_x * 10 + 5, y).l = 0.5 ;
        }

        start_y -= 1 ;
        break ;
    }

    solution.erase(solution.begin() ) ;

  }

  for ( int x = 10 * start_x + 1 ; x < 10 * start_x + 10 ; x++ )
      draw_maze->getPixel(x, 10 * (start_y+1) ).l = 1 ;

  return draw_maze ;
}

void SquareMaze::makeMaze(int width, int height )
{
  // Creating a Disjoint Set with Width * Height Elements.
  // These Nodes will represent a Tile: Represented by Map with Key Tile, Right, Down

  // Set Seed and Parameters
  sleep(2) ;
  width_ = width ;
  height_ = height ;

  // Create our Disjoint Set and Tiles with all Walls
  layout.addelements(width * height ) ;

  for ( int i = 0 ; i < width * height ; i++ )
    tile.insert( pair<int, pair<bool, bool> > (i, make_pair(1, 1) ) );

  // Randomly Delete Walls. Stops when size of any node results in the total tiles
  int total = width * height ;
  int test = 0 ;

  while ( layout.size(rand() % total) != total )
  {
    // Get rid of a Random Edge : 0 means Right and 1 means Down for Direction
    int x_edge = rand() % width ;
    int y_edge = rand() % height ;
    int dir_edge = rand() % 2 ;
    int direction ;

    if ( !dir_edge )
      direction = 1 ;
    else
      direction = width ;

    // Check if the Edge is on the Border of Maze
    if ( !(y_edge == height - 1 && dir_edge == 1) && !(x_edge == width - 1 && dir_edge == 0) )
    {
      int tile_num = x_edge + y_edge * width_ + direction ;

      // Check Out of Bounds and
      if (  tile_num < height_ * width_ )
      {
        auto specific_tile = tile.find( x_edge + width_ * y_edge ) ;

        if ( !(specific_tile->second.first == 0 && dir_edge == 0) && !(specific_tile->second.second == 0 && dir_edge == 1) )
          // Check if this results in Cycle or not
          if ( layout.find( x_edge + y_edge * width) != layout.find(x_edge + y_edge * width + direction) )
          {
            if ( !dir_edge )
              specific_tile->second.first = 0 ;

            else
              specific_tile->second.second = 0 ;

            layout.setunion(x_edge + y_edge * width_, tile_num ) ;
          }
      }
    }
  }


}

void SquareMaze::setWall (int x, int y, int dir, bool exists )
{
  int tile_num = x + y * width_  ;
  auto specific_tile = tile.find(tile_num ) ;

  if ( !dir )
    specific_tile->second.first = exists ;
  else
    specific_tile->second.second = exists ;

}

vector<int> SquareMaze::solveMaze ()
{
  vector<int> best_path ;
  vector<int> current_path ;
  vector<bool> traveled ;
  stack<int> directions ;

  for ( int i = 0 ; i < width_ * height_ ; i++ )
    traveled.push_back(0) ;

  stack<int> DFS_X ;
  stack<int> DFS_Y ;

  stack <int> small_x_curr ;
  int small_x_best ;

  DFS_X.push(0) ;
  DFS_Y.push(0) ;

  while ( !(DFS_X.empty()) && !(DFS_Y.empty() ) )
  {
    int x_coord = DFS_X.top() ;
    int y_coord = DFS_Y.top() ;

    if ( traveled.at( x_coord + width_ * y_coord ) )
    {

          DFS_X.pop() ;
          DFS_Y.pop() ;

          if ( current_path.size() > best_path.size() && y_coord == height_ - 1 )
          {
            best_path = current_path ;
            small_x_best = x_coord ;
          }

          else if ( current_path.size() == best_path.size() && y_coord == height_ - 1 )
            if ( x_coord < small_x_best )
            {
              best_path = current_path ;
              small_x_best = x_coord ;
            }

          if ( !directions.empty() )
            directions.pop() ;

          if ( !current_path.empty() )
            current_path.erase( current_path.end() - 1 ) ;

        continue ;
    }

    int test = x_coord + width_ * y_coord  ;
    traveled.at( x_coord + width_ * y_coord ) = 1 ;

    if ( !directions.empty() )
      current_path.push_back(directions.top() ) ;

    // Case 1: Can Travel Right
    if ( canTravel(x_coord, y_coord, 0 )  )
    {
      if ( !traveled.at(x_coord + 1 + width_ * y_coord) )
      {
        DFS_X.push(x_coord+1) ;
        DFS_Y.push(y_coord) ;
        directions.push(0) ;
      }
    }

    // Case 2: Can Travel Down
    if ( canTravel(x_coord, y_coord, 1 ) )
    {
      if( !traveled.at(x_coord + width_ * (y_coord + 1) ) )
      {
        DFS_X.push(x_coord) ;
        DFS_Y.push(y_coord+1) ;
        directions.push(1) ;
      }
    }

    // Case 3: Can Travel Left
    if ( canTravel(x_coord, y_coord, 2 ) )
    {
      if ( !traveled.at(x_coord - 1 + width_ * y_coord) )
      {
        DFS_X.push(x_coord-1) ;
        DFS_Y.push(y_coord) ;
        directions.push(2) ;
      }
    }

    // Case 4: Can Travel Up
    if ( canTravel(x_coord, y_coord, 3 ) )
    {
      if ( !traveled.at(x_coord + width_ * (y_coord-1) ) )
      {
        DFS_X.push(x_coord) ;
        DFS_Y.push(y_coord-1) ;
        directions.push(3) ;
      }
    }
  }

  return best_path ;
}
