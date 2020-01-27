/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1

  ListNode* current = head_ ;
  ListNode* curr_next ;
  for ( int i = 0 ; i < length_ ; i++ )
  {
      curr_next = current->next ;
      delete current ;
      current = curr_next ;
  }


}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ~List() ;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* new_head = new ListNode( ndata) ;
  length_ += 1 ;

  if( head_ == NULL )
  {
	tail_ = new_head ;
	head_ = new_head ;
  }
  else
  {
	new_head->next = head_ ;
	head_->prev = new_head ;
	head_ = new_head ;
  }




}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1

  ListNode* new_tail = new ListNode( ndata) ;
  length_ += 1 ;

  if ( tail_ == NULL )
  {
	tail_ = new_tail ;
	head_ = new_tail ;
  }
  else
  {
	new_tail->prev = tail_ ;
	tail_->next = new_tail ;
	tail_ = new_tail ;
  }

}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1


  // Temp1 will carry the Head Node. Temp2 will contain Head->Next
  ListNode* temp1 = endPoint ;
  ListNode* temp2 ;
  bool continue_reverse = true ;


  for( int i = 0 ; i < length_ ; i++ )
  {
	if ( !continue_reverse )
	{
		break ;
	}

	if( temp1 == startPoint )
	{
		continue_reverse = false ;
	}

	temp2 = temp1->next ;

	temp1->next = temp1->prev ;
	temp1->prev = temp2 ;

	temp1 = temp1->next ;

  }

  ListNode* temp3 = startPoint ;
  ListNode* temp4 = endPoint ;

  if ( endPoint == tail_ && startPoint == head_ )
  {
	  head_ = temp4 ;
	  tail_ = temp3 ;
  }

  else if ( startPoint == head_ )
  {
	  endPoint->prev = NULL ;
	  head_ = endPoint ;
  }

  else if ( endPoint == tail_ )
  {
	  startPoint->next = NULL ;
	  tail_ = startPoint ;
  }

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1

  int num_iter = length_ / n ;
  int leftover = length_ % n ;
  ListNode* startPoint = head_ ;
  ListNode* endPoint = head_ ;
  ListNode* new_start ;
  ListNode* prev_end = NULL ;
  ListNode* temp1 = head_ ;
  ListNode* temp2 = tail_ ;

  for ( int i = 0 ; i < num_iter ; i++ )
  {
	  // Determine End Point
	  for ( int j = 0 ; j < n - 1 ; j++ )
	  {
		  endPoint = endPoint->next ;
	  }


	  new_start = endPoint->next ;
	  reverse(startPoint, endPoint ) ;

	  startPoint->next = new_start ;

	  endPoint->prev = prev_end ;

	  if( prev_end != NULL )
	  {
		prev_end->next = endPoint ;
	  }

	  prev_end = startPoint ;

	  startPoint = new_start ;
	  endPoint = new_start ;
  }

  if ( leftover != 0 )
  {
	  for ( int j = 0 ; j < leftover-1 ; j++ )
	  {
		  endPoint = endPoint->next ;
	  }

	  new_start = endPoint->next ;
	  reverse(startPoint, endPoint) ;

	  startPoint->next = new_start ;
	  endPoint->prev = prev_end ;
	  prev_end->next = endPoint ;

  }



}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

  ListNode* curr = head_ ;
  ListNode* moved = head_->next ;
  ListNode* next_curr = moved->next ;

  for (int i = 0 ; i < length_ ; i++ )
  {
	  if ( next_curr == NULL )
	  {
		  break ;
	  }

	  curr->next = next_curr ;
	  next_curr->prev = curr ;

	  moved->prev = tail_ ;
	  moved->next = NULL ;
	  tail_->next = moved ;

	  tail_ = moved ;

	  curr = next_curr ;
	  moved = curr->next ;
	  next_curr = moved->next ;

  }





}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode* temp_node = start ;

  for(int i = 0 ; i < length_ ; i++ )
  {
    if ( i == splitPoint )
    {

      temp_node->prev->next = NULL ;
      temp_node->prev = NULL ;

      break ;
    }

    temp_node = temp_node->next ;

  }

  return temp_node ;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  ListNode* new_head ;
  ListNode* temp_mov ;

  if ( first == NULL || second == NULL )
    return NULL ;

  // DETERMINING HEAD OF FINAL LIST
  if ( first->data < second->data )
  {
    new_head = first ;
    first = first->next ;
  }

  else
  {
    new_head = second ;
    second = second->next ;
  }

  temp_mov = new_head ;


  // FINALIZING SORTED LIST
  while ( (first != NULL) && (second != NULL)  )
  {
      if ( first->data < second->data )
      {
        temp_mov->next = first ;
        first->prev = temp_mov ;
        first = first->next ;
      }

      else
      {
        temp_mov->next = second ;
        second->prev = temp_mov ;
        second = second->next ;
      }

      temp_mov = temp_mov->next ;

  }

  // ADDING REMAINING ELEMENTS
  if ( first == NULL )
  {
    temp_mov ->next = second ;
    second->prev = temp_mov ;
  }

  if ( second == NULL )
  {
    temp_mov ->next = first ;
    first->prev = temp_mov ;
  }


  return new_head ;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

  if ( chainLength == 1 )
    return start ;

  List<T> second_list = split( chainLength/2 ) ;
  this->sort() ;
  second_list.sort() ;
  
  this->mergeWith(second_list) ;


  return this->head_ ;
}
