
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1 ;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2 * currentIdx ;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return  2 * currentIdx + 1 ;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return int(currentIdx/2) ;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child

    if ( leftChild( currentIdx) < _elems.size() )
      return true ;

    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if ( !hasAChild(currentIdx) )
      return currentIdx ;

    if ( rightChild(currentIdx) >= _elems.size() )
      return leftChild(currentIdx) ;

    if ( higherPriority( _elems.at(leftChild(currentIdx) ), _elems.at(rightChild(currentIdx)  )  ) )
      return leftChild(currentIdx) ;

    return rightChild(currentIdx)  ;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.

    if ( !hasAChild(currentIdx) )
      return ;

    size_t max_prior =  maxPriorityChild(currentIdx) ;
    size_t priority_parent = parent( max_prior) ;

    if ( _elems.at(priority_parent) > _elems.at(max_prior) )
      std::swap( _elems.at(priority_parent), _elems.at(max_prior) ) ;

    heapifyDown( max_prior ) ;

}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying

    _elems.push_back( T() ) ;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm

    _elems.push_back( T() ) ;

    for ( unsigned long i = 0 ; i < elems.size() ; i++ )
      _elems.push_back( elems.at(i) ) ;

    for ( int i = int( elems.size() / 2 ) ; i != 0 ; i-- )
      heapifyDown(i) ;

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority

    size_t deleted = root() ;
    T value = _elems.at(deleted) ;

    std::swap( _elems.at(root()), _elems.at( _elems.size() - 1 ) ) ;
    _elems.erase( _elems.end() - 1 ) ;
    heapifyDown( root() ) ;

    return value ;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems.at( maxPriorityChild(root() ) );
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap

    _elems.push_back( elem ) ;
    heapifyUp( _elems.size() - 1 ) ;
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update

    _elems.at( 1 + idx)  = elem ;

    if ( hasAChild(1 + idx ) )
      if ( _elems.at(maxPriorityChild(1 + idx) ) < _elems.at( 1 + idx )  )
        heapifyDown(1 + idx ) ;

    if ( _elems.at(parent(1 + idx) ) > _elems.at(1+idx) )
      heapifyUp(1+idx) ;
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty

    if (_elems.size() == 1 )
      return true ;

    return false ;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
