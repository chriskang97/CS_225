/* Your code here! */
#include "dsets.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std ;

void DisjointSets::addelements (int num)
{
  for ( int i = curr ; i < curr + num ; i++ )
    dset.push_back(-1) ;

  curr = curr + num ;
}

int DisjointSets::find (int elem)
{
  int root = elem ;

  if ( dset.at(root) < 0 )
    return root ;

  while( dset.at(root) >= 0 )
    root = dset.at(root) ;

  dset.at(elem) = root ;

  return root ;
}

void DisjointSets::setunion (int a, int b)
{
  int num_a = size(a) ;
  int num_b = size(b) ;
  int root_a = a ;
  int root_b = b ;

  if ( num_a < num_b )
  {
    root_a = find(root_a) ;
    root_b = find(root_b) ;

    dset.at(root_a) = root_b ;
    dset.at(root_b) -= num_a ;
  }

  else
  {
    root_a = find(root_a) ;
    root_b = find(root_b) ;

    dset.at(root_b) = root_a ;
    dset.at(root_a) -= num_b ;
  }


}

int DisjointSets::size (int elem)
{
  return -dset.at( find(elem) ) ;
}
