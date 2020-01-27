#include "List.h"

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "cs225/catch/catch.hpp"
#include "tests/tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


using namespace std ;
using namespace cs225 ;

int main() {



  /*List<unsigned> list1;
	List<unsigned> list2 ;

  for ( unsigned i = 1; i < 9; i=i+2) { list1.insertBack(i); }
	for ( unsigned i = 5; i < 8; i++ ) { list2.insertBack(i); }

  cout<<list1<<endl ;
	cout<<list2<<endl ;


  list1.mergeWith(list2);
	List<unsigned> merge(list1.begin(), list1.end () ) ;

  cout<<list1<<endl ; */

	List<unsigned> list1 ;
	list1.insertBack(9);
	list1.insertBack(2);
	list1.insertBack(5);
	list1.insertBack(1);
	list1.insertBack(3);
	list1.insertBack(8);
	list1.insertBack(2);
	list1.insertBack(0);
	list1.insertBack(7);
	list1.insertBack(9);

  cout<<list1<<endl ;

	list1.sort() ;

  cout<<list1<<endl ;
	
  return 0;
}
