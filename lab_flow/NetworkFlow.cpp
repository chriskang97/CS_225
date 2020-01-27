/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"
#include <iostream>

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE

  flow_ = startingGraph ;
  residual_ = startingGraph ;

  vector<Edge> edge_list = g_.getEdges() ;

  for ( auto it = edge_list.begin() ; it != edge_list.end() ; it++ )
  {
    flow_.setEdgeWeight( it->source, it->dest, 0 ) ;
    residual_.insertEdge(it->dest, it->source ) ;
    residual_.setEdgeWeight( it->dest, it->source, 0 ) ;
  }

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE

  int min_weight = -1 ;
  int curr_edge ;

  for ( unsigned long i = 0 ; i < path.size() - 1; i++ )
  {
    curr_edge = residual_.getEdgeWeight( path.at(i), path.at(i+1) ) ;

    if ( curr_edge < min_weight || min_weight == -1 )
      min_weight = curr_edge ;
  }

  return min_weight ;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE

  int finished = 0 ;
  vector<Vertex> path ;
  int min_weight ;
  int curr_edge ;


  while (findAugmentingPath(source_, sink_, path) )
  {
    min_weight = pathCapacity(path) ;

    for ( unsigned long i = 0 ; i < path.size() - 1; i++ )
    {
      // Updating Flow/Residual Graph. If Edge doesn't exist, then it must be a backward edge.
      if ( flow_.edgeExists( path.at(i), path.at(i+1) ) )
      {
        curr_edge = flow_.getEdgeWeight( path.at(i), path.at(i+1) ) ;
        flow_.setEdgeWeight( path.at(i), path.at(i+1), curr_edge + min_weight ) ;

        curr_edge = residual_.getEdgeWeight(path.at(i), path.at(i+1)  ) ;
        residual_.setEdgeWeight( path.at(i), path.at(i+1), curr_edge - min_weight ) ;

        curr_edge = residual_.getEdgeWeight(path.at(i+1), path.at(i)  ) ;
        residual_.setEdgeWeight( path.at(i+1), path.at(i), curr_edge + min_weight ) ;
      }

      else
      {
        curr_edge = flow_.getEdgeWeight( path.at(i+1), path.at(i) ) ;
        flow_.setEdgeWeight( path.at(i+1), path.at(i), curr_edge - min_weight ) ;

        curr_edge = residual_.getEdgeWeight(path.at(i), path.at(i+1)  ) ;
        residual_.setEdgeWeight( path.at(i), path.at(i+1), curr_edge + min_weight ) ;

        curr_edge = residual_.getEdgeWeight(path.at(i+1), path.at(i)  ) ;
        residual_.setEdgeWeight( path.at(i+1), path.at(i), curr_edge - min_weight ) ;
      }
    }



  }

  vector <Vertex> adjacent = flow_.getAdjacent( source_ ) ;
  maxFlow_ = 0 ;

  for ( unsigned long i = 0 ; i < adjacent.size() ; i++ )
    maxFlow_ += flow_.getEdgeWeight( source_, adjacent.at(i) ) ;


  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
