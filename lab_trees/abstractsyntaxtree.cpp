#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...

    stack <double> s ;

    if ( root != NULL )
      eval( root, s ) ;


    return s.top() ;
}

bool AbstractSyntaxTree::eval( Node* subRoot, stack<double> &s ) const
{
  if (subRoot == NULL )
    return true ;

  if ( eval(subRoot->left, s ) == true )
    if ( eval(subRoot->right, s ) == true )
    {
      if ( subRoot->left != NULL && subRoot->right != NULL  )
      {

        // IF BOTH  LEFT AND RIGHT HAVE OPERATORS
        if ( (subRoot->left->elem == "+" || subRoot->left->elem == "-" || subRoot->left->elem == "*" || subRoot->left->elem == "/") && (subRoot->right->elem == "+" || subRoot->right->elem == "-" || subRoot->right->elem == "*" || subRoot->right->elem == "/") )
        {
          double value1 = s.top() ;
          s.pop() ;

          double value2 = s.top() ;
          s.pop() ;

          s.push(calc(subRoot->elem, value1, value2) ) ;

        }

        // IF LEFT HAS OPERATOR
        else if ( subRoot->left->elem == "+" || subRoot->left->elem == "-" || subRoot->left->elem == "*" || subRoot->left->elem == "/"  )
        {
          double value1 = s.top() ;
          s.pop() ;

          s.push(calc(subRoot->elem, value1, std::stod(subRoot->right->elem) ) ) ;
        }

        // IF RIGHT HAS OPERATOR
        else if ( subRoot->right->elem == "+" || subRoot->right->elem == "-" || subRoot->right->elem == "*" || subRoot->right->elem == "/" )
        {
          double value2 = s.top() ;
          s.pop() ;

          s.push(calc(subRoot->elem, std::stod(subRoot->left->elem), value2 )  );
        }

        // IF LEFT AND RIGHT ARE BOTH NUMBERS
        else
          s.push( calc(subRoot->elem, std::stod(subRoot->left->elem), std::stod(subRoot->right->elem) ) );
      }
    }


  return true ;
}

double AbstractSyntaxTree::calc( std::string oper, double first, double second ) const
{
  if ( oper == "+")
    return first + second ;

  if ( oper == "-")
    return first - second ;

  if ( oper == "*")
    return first * second ;

  if ( oper == "/")
    return first / second ;

  return 0 ;
}
