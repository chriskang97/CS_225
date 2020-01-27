/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <iostream>
using namespace std ;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here

    Node* t_right = t->right ;

    t->right = t_right->left ;
    t_right->left = t ;

    int height_left = 0 ;
    int height_right = 0 ;
    int path = 0 ;

    getHeight(t->right, height_right, path ) ;

    path = 0 ;
    getHeight(t->left, height_left, path ) ;

    t->height = height_right - height_left ;

    if ( root == t )
      root = t_right ;

    t = t_right ;

    height_left = 0 ;
    height_right = 0 ;
    path = 0 ;

    getHeight(t_right->right, height_right, path ) ;

    path = 0 ;
    getHeight(t_right->left, height_left, path ) ;

    t_right->height = height_right - height_left ;


}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here

    Node* t_left = t->left ;

    t->left = t_left->right ;
    t_left->right = t ;

    int height_left = 0 ;
    int height_right = 0 ;
    int path = 0 ;

    getHeight(t->right, height_right, path ) ;

    path = 0 ;
    getHeight(t->left, height_left, path ) ;

    t->height = height_right - height_left ;

    if ( root == t )
      root = t_left ;

    t = t_left ;

    height_left = 0 ;
    height_right = 0 ;
    path = 0 ;

    getHeight(t_left->right, height_right, path ) ;

    path = 0 ;
    getHeight(t_left->left, height_left, path ) ;

    t_left->height = height_right - height_left ;


}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here

    if ( subtree->height > 1 )
    {
      if ( subtree->right->height > 0 )
        rotateLeft(subtree) ;

      else
        rotateRightLeft(subtree) ;
    }

    else if (subtree->height < -1 )
    {
      if ( subtree->left->height < 0 )
        rotateRight(subtree) ;

      else
        rotateLeftRight(subtree) ;
    }

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here

    if ( root == NULL )
    {
      root = new Node(key, value ) ;
      return ;
    }

    if ( subtree == NULL )
      return ;

    if( subtree->key < key && subtree->right == NULL )
    {
      subtree->right = new Node(key, value ) ;

      /*if (  subtree->left != NULL )
        subtree->height = 0 ;
      else
        subtree->height = 1 ;

      return ;*/
    }

    else if( subtree->key > key && subtree->left == NULL )
    {
      subtree->left = new Node(key, value ) ;

      /*if (subtree->right != NULL )
        subtree->height = 0 ;

      else
        subtree->height = -1 ;

      return ;*/
    }

    else
    {
      if ( subtree->key < key )
      {
        //int temp_height = subtree->right->height ;

        insert( subtree->right, key, value ) ;

        //if ( subtree->right->height != 0 || temp_height == subtree->right->height )
          //subtree->height = subtree->height + 1 ;
      }

      else
      {
        //int temp_height = subtree->left->height ;

        insert( subtree->left, key, value ) ;

        //if ( subtree->left->height != 0 || temp_height == subtree->left->height )
          //subtree->height = subtree->height - 1 ;
      }

    }

    int height_left = 0 ;
    int height_right = 0 ;
    int path = 0 ;

    getHeight(subtree->right, height_right, path ) ;

    path = 0 ;
    getHeight(subtree->left, height_left, path ) ;

    subtree->height = height_right - height_left ;

    rebalance(subtree) ;

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{

    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key ) ;
    }
    else if (key > subtree->key) {
        // your code here

        remove(subtree->right, key) ;

    }
    else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            subtree = NULL ;
            return ;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* in_order = subtree->right ;
            Node* temp = subtree ;

            while(in_order->left != NULL  )
            {
              if ( in_order->left->left == NULL )
                temp = in_order ;

              in_order = in_order->left ;
            }

            swap(subtree, in_order ) ;

            if ( temp == subtree )
            {
              temp->right = in_order->right ;
              temp->height -= 1 ;
            }

            else
            {
              temp->left = in_order->right  ;
              temp->height += 1 ;
            }


        } else {
            /* one-child remove */
            // your code here

            if ( subtree->left != NULL )
            {
              subtree = subtree->left ;
            }

            else
            {
              subtree = subtree->right ;
            }
        }
        // your code here
    }

    int height_left = 0 ;
    int height_right = 0 ;
    int path = 0 ;

    getHeight(subtree->right, height_right, path ) ;

    path = 0 ;
    getHeight(subtree->left, height_left, path ) ;

    subtree->height = height_right - height_left ;

    rebalance(subtree) ;
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node* subroot, int & height, int &path )
{
  if ( subroot == NULL )
  {
    if( path > height )
      height = path ;

    return -1 ;
  }

  path += 1 ;

  getHeight(subroot->left, height, path ) ;
  getHeight(subroot->right, height, path ) ;

  path -= 1 ;

  return -1 ;
}
