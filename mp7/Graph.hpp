#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2

  return vertexMap.size() ;
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2

  return adjList.find(v)->second.size() ;
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));

  std::list<edgeListIter> temp ;

  vertexMap.insert( std::pair<std::string, V &> (key, v) ) ;
  adjList.insert( std::pair<std::string, std::list<edgeListIter>> (key, temp ) ) ;

  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  std::list<edgeListIter> delete_edge = adjList.find(key)->second ;

  for ( auto it = delete_edge.begin() ; it != delete_edge.end() ; it++ )
    edgeList.erase( *it ) ;

  vertexMap.erase( key ) ;
  adjList.erase( key) ;

}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));


  string key1 = v1.key() ;
  string key2 = v2.key() ;

  auto vertex1 = adjList.find(key1) ;
  auto vertex2 = adjList.find(key2) ;
  edgeList.push_front(e) ;


  vertex1->second.push_front( edgeList.begin() ) ;
  vertex2->second.push_front( edgeList.begin() ) ;


  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2

  auto vertex1 = adjList.find(key1) ;
  auto vertex2 = adjList.find(key2) ;

  // Removing from Edge List
  for ( auto it = edgeList.begin() ; it != edgeList.end() ; it++ )
  {
    if ( (it->get().source().key() == key1 && it->get().dest().key() == key2) || (it->get().source().key() == key2 && it->get().dest().key() == key1))
    {
      edgeList.erase(it) ;
      break ;
    }

  }

  // Removing from Adajacent List
  auto edges1 = adjList.find(key1) ;
  auto edges2 = adjList.find(key2) ;

  // Deleting Edge from Vertex 1 Adjacent List
  for ( auto it = edges1->second.begin() ; it != edges1->second.end() ; it++ )
  {
    if (  ( (**it).get().source().key() == key1 && (**it).get().dest().key() == key2) ||  ( (**it).get().source().key() == key2 && (**it).get().dest().key() == key1))
    {
      edges1->second.erase( it ) ;
      break ;
    }

  }

  // Deleting Edge from Vertex 2 Adjacent List
  for ( auto it = edges2->second.begin() ; it != edges2->second.end() ; it++ )
  {
    if ( ((**it).get().source().key() == key1 && (**it).get().dest().key() == key2) || ( (**it).get().source().key() == key2 && (**it).get().dest().key() == key1) )
    {
      edges2->second.erase( it ) ;
      break ;
    }
  }

}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2

  string key1 = it.get().source().key() ;
  string key2 = it.get().dest().key() ;

  removeEdge(key1, key2) ;


}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;

  auto vertex = adjList.find(key) ;

  for ( auto it = vertex->second.begin() ; it != vertex->second.end() ; it++ )
    edges.push_front( **it ) ;

  return edges ;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2

  auto vertex1 = adjList.find(key1) ;
  auto vertex2 = vertexMap.find(key2) ;

  for ( auto it = vertex1->second.begin() ; it != vertex1->second.end() ; it++ )
  {
    if ( (**it).get().dest() == vertex2->second ) //&& (**it).get().directed()
      return true ;

    if ( !(**it).get().directed() )
    {
      if ( (**it).get().source() == vertex2->second )
        return true ;
    }

  }

  return false;
}
