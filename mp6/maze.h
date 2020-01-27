/* Your code here! */

#pragma once
#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"
#include <map>


using namespace std ;
using namespace cs225 ;

class SquareMaze
{
  public :
    SquareMaze () ;
    bool canTravel (int x, int y, int dir ) const ;
    PNG* drawMaze () const ;
    PNG* drawMazeWithSolution () ;
    void makeMaze (int width, int height ) ;
    void setWall 	(int x, int y, int dir, bool exists ) ;
    vector<int> solveMaze () ;

  private :
    DisjointSets layout ;
    map<int, pair<bool, bool> > tile ;
    int width_ = 0 ;
    int height_ = 0 ;



};
