/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    // Tie Breaker
    if ( first[curDim] == second[curDim] )
      return first < second ;

    // Regular Comparision
    if( first[curDim] < second[curDim] )
      return true ;

    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

     double tar_curr = 0 ;
     double tar_pot = 0 ;

     for ( int i = 0 ; i < Dim ; i ++ )
     {
       tar_curr += ( target[i] - currentBest[i] ) * ( target[i] - currentBest[i] )  ;
       tar_pot += ( target[i] - potential[i] ) * ( target[i] - potential[i] )  ;
     }

     if ( tar_curr == tar_pot )
      return potential < currentBest ;

     if ( tar_pot < tar_curr )
      return true ;

     return false;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quick_select( vector<Point<Dim>> & newPoints, int i, int j, int left_bound, int right_bound, int curr_dim, int desire_index )
{
    // LIST OF STEPS FOR QUICK SELECT. THIS IS USED TO FIND THE MEDIAN AT A SPECIFIC INDEX.
    //
    // 1). CHOOSE A RANDOM INDEX. SWAP THAT TO THE RIGHT BOUND. (IGNORING TO DO RANDOM INDEX AND JUST START AT RIGHT BOUND )
    // 2). UPDATE I AND J SO THAT: LEFT_POINT >= RIGHT BOUND && RIGHT POINT < RIGHT BOUND.
    // 3). IF DONE SUCCESSFULLY, SWAP I AND J VALUES AND REPEAT STEP 2.
    // 4). IF I AND J EVER CROSS EACH OTHERS PATH THEN SWAP THE RIGHT BOUND WITH THE LEFT POINT.
    // 5). IF THE SWAPPED POINT AFTER THIS CROSS WAS LOWER THAN THE DESIRED INDEX, UPDATE THE LEFT BOUND CONDITION. HIGHER THAN DESIRE INDEX UPDATE RIGHT BOUND.
    // 6). WHEN I AND J ARE AT THE SAME INDEX, THEN WE ARE DONE AND JUST HAVE TO DO 1 MORE SWAP WITH THE RIGHT BOUND.

    int pivot = right_bound  ;

    if ( left_bound == right_bound )
      return newPoints.at(left_bound) ;

    // KEEP UPDATING UNTIL CONDITIONS ARE SATISFIED
    while( smallerDimVal( newPoints.at(i), newPoints.at(pivot), curr_dim )   && i < right_bound )
      i += 1 ;

    while( smallerDimVal( newPoints.at(pivot), newPoints.at(j), curr_dim )  && j > left_bound  )
      j -= 1 ;

    //cout<<newPoints.at(j)<<endl ;


    if ( i == desire_index )
    {
      if ( i >= j)
        iter_swap( newPoints.begin() + i, newPoints.begin() + pivot ) ;
      else
        iter_swap( newPoints.begin() + i, newPoints.begin() + j ) ;

      return newPoints.at(desire_index) ;
    }

    // WHEN I PASSES J
    if ( i >= j )
    {
      iter_swap( newPoints.begin() + i, newPoints.begin() + pivot ) ;

      if ( i < desire_index )
      {
        left_bound = i + 1 ;
        return quick_select( newPoints, left_bound, right_bound - 1, left_bound, right_bound, curr_dim, desire_index ) ;
      }

      else
      {
        right_bound = i - 1 ;
        return quick_select( newPoints, left_bound, right_bound - 1, left_bound, right_bound, curr_dim, desire_index ) ;
      }


    }

    // WHEN I EQUALS TO J, END THE QUICK SELECT
    // else if ( i == j  )
    // {
    //   iter_swap( newPoints.begin() + i, newPoints.begin() + pivot ) ;
    //   return quick_select( newPoints, left_bound, right_bound - 1, left_bound, right_bound, curr_dim, desire_index ) ;
    // }


    // CONDITION WHEN I AND J DON'T CROSS
    iter_swap( newPoints.begin() + i, newPoints.begin() + j ) ;
    return quick_select( newPoints, left_bound, right_bound - 1, left_bound, right_bound, curr_dim, desire_index ) ;


}

template <int Dim>
void KDTree<Dim>::Build_KD(vector<Point<Dim>>& newPoints, int left_range, int right_range, int curr_dim, KDTreeNode* subroot   )
{
  int median_index = (left_range + right_range ) / 2 ;
  Point<Dim> median ;

  if ( right_range - left_range == 1  )
  {

    if ( ! smallerDimVal(newPoints.at(left_range), newPoints.at(right_range), curr_dim ) )
      iter_swap(newPoints.begin() + left_range, newPoints.begin() + right_range ) ;

    subroot->point = newPoints[median_index];
    subroot->right = new KDTreeNode ;
    subroot->right->point = newPoints[right_range] ;

    return ;
  }

  if ( right_range - left_range == 0 )
  {
    subroot->point = newPoints[left_range] ;
    return ;
  }


  else
  {
    median =  quick_select( newPoints, left_range, right_range - 1 , left_range , right_range, curr_dim, median_index ) ;

    subroot->point = median ;
    subroot->left = new KDTreeNode() ;
    subroot->right = new KDTreeNode() ;

    Build_KD( newPoints, left_range, median_index - 1, (curr_dim + 1) % Dim, subroot->left  ) ;
    Build_KD( newPoints, median_index + 1, right_range, (curr_dim + 1) % Dim, subroot->right  ) ;

  }


}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     root = new KDTreeNode() ;

     if ( newPoints.empty() )
       return ;

    vector<Point<Dim>> quick_sel = newPoints ;

    Build_KD(quick_sel, 0, int(quick_sel.size() - 1), 0, root  ) ;

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   other.root = root ;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  ~KDTree() ;
  this->root = rhs.root ;

  return *this;
}

template <int Dim>
void KDTree<Dim>::delete_help( KDTreeNode*  subroot )
{
  if ( subroot == NULL )
    return ;

  delete_help( subroot->left ) ;

  if(subroot->left != NULL )
    delete subroot->left ;

  delete_help( subroot->right ) ;

  if(subroot->right != NULL )
    delete subroot->right ;

}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   delete_help(root) ;
   delete root ;
}


template <int Dim>
void KDTree<Dim>::help_nn(const Point<Dim> & query, Point<Dim> & best, KDTreeNode* subroot, int curr_dim, bool & initial ) const
{

  if ( subroot == NULL )
    return ;

  double radius = 0 ;
  double split_dist = 0 ;

  // Setting Initial Point
  if ( subroot->left == NULL && subroot->right == NULL )
    if ( !initial )
    {
      best = subroot->point ;
      initial = true ;
      return ;
    }

  if ( smallerDimVal(query, subroot->point, curr_dim ) && subroot->left != NULL  )
      help_nn( query, best, subroot->left, (curr_dim+1) % Dim, initial ) ;

  else if ( subroot->right != NULL )
      help_nn( query, best, subroot->right, (curr_dim+1) % Dim, initial ) ;


  // Found a new Best Match.
  if ( shouldReplace(query, best, subroot->point ) && initial )
    best = subroot->point ;


  if ( smallerDimVal(query, subroot->point, curr_dim ) && subroot->right != NULL)
  {
    for ( unsigned i = 0 ; i < Dim ; i++ )
      radius += (best[i] - query[i]) * (best[i] - query[i])  ;

    split_dist = ( subroot->point[curr_dim] - query[curr_dim] ) * ( subroot->point[curr_dim] - query[curr_dim] ) ;

    if ( split_dist <= radius )
      help_nn( query, best, subroot->right, (curr_dim+1) % Dim, initial ) ;
  }

  else if ( subroot->left != NULL)
  {
    for ( unsigned i = 0 ; i < Dim ; i++ )
      radius += (best[i] - query[i]) * (best[i] - query[i])  ;

    split_dist = ( subroot->point[curr_dim] - query[curr_dim] ) * ( subroot->point[curr_dim] - query[curr_dim] ) ;

    if ( split_dist <= radius )
      help_nn( query, best, subroot->left, (curr_dim+1) % Dim, initial ) ;
  }



}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> best ;
    Point<Dim> desire = query ;
    bool initial = false ;
    help_nn(desire, best, root, 0, initial )  ;

    return best ;
}
