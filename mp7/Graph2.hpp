#include <queue>
#include <algorithm>
#include <string>
#include <list>

#include <unordered_map>
#include <iostream>

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */

using namespace std ;
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;

  unordered_map<string, string > marked_V ;
  unordered_map<string, list< pair<E, string> > > marked_E ;
  queue<V> curr_path ;
  unordered_map< string, string> previous_map ;

  // Craete another Dict for DIstance -> Path

  V start_node = vertexMap.find(start)->second ;

  curr_path.push(start_node ) ;

  // Setting Each Vertex/Edge to be Unvisted.
  for ( auto i = vertexMap.begin() ; i != vertexMap.end() ; i++ )
  {
    list< pair<E, string> > vert_edge ;

    previous_map.insert( pair<string, string> (i->first, "") ) ;
    marked_V.insert( pair<string, string> ( i->first, "UNVISITED") ) ;

    list<edgeListIter> edges = adjList.find( i->first )->second ;

    for ( auto it = edges.begin() ; it != edges.end() ; it++ )
      vert_edge.push_back( make_pair( (**it).get(), "UNVISITED") ) ;

    marked_E.insert( pair<string, list< pair<E, string> > > (i->first, vert_edge) ) ;
  }

  bool reached = false ;
  int distance = 0 ;

  // Running BFS traversal now
  while ( !curr_path.empty() && !reached )
  {
    // Obtaining Current Node
    V curr_node = curr_path.front() ;
    curr_path.pop() ;
    string key = curr_node.key() ;

    list< pair<E,string> > vert_edge = marked_E.find(key)->second ;
    string second_node ;

    // Found the ending point so start mapping path
    if ( key == end )
    {
      list<string> new_path ;
      string trace = key ;

      while ( trace != start )
      {
        new_path.push_front(trace) ;
        trace = previous_map.find(trace)->second ;
      }

      new_path.push_front(trace) ;

      if ( path.empty() )
        path = new_path ;

      else if ( new_path.size() < path.size() )
        path = new_path ;
    }

    // If Node is already visisted, skip it.
    if (marked_V.find(key)->second == "VISITED")
      continue ;
    else
      marked_V.find(key)->second = "VISITED" ;

    // Obtain all Adjacent Paths
    for ( auto it = vert_edge.begin() ; it != vert_edge.end() ; it++ )
    {
      // Assuming all edges are undirected. Check Condition with isAdjacent function
      if ( key == it->first.dest().key() )
        second_node = it->first.source().key() ;
      else
        second_node = it->first.dest().key() ;

      if ( marked_V.find(second_node)->second == "UNVISITED" && it->second == "UNVISITED" && isAdjacent(key, second_node) )
      {
        if ( previous_map.find(second_node)->second == "" )
          previous_map.find( second_node)->second = key ;

        curr_path.push(second_node) ;
      }

    }
  }





  return path;
}
