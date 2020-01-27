/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */

    // Start off Player 1
    string player1 = "p1" ;
    string player2 = "p2" ;

    for ( int tokens = startingTokens ; tokens >= 0 ; tokens-- )
    {
      g_.insertVertex(player1 + "-" + to_string(tokens) ) ;
      g_.insertVertex(player2 + "-" + to_string(tokens) ) ;
    }

    // Creating Edges

    for ( int tokens = startingTokens ; tokens > 0 ; tokens-- )
    {
      if ( tokens == 1 )
      {
        g_.insertEdge( player1 + "-" + to_string(tokens), player2 + "-" + to_string(tokens-1) ) ;
        g_.insertEdge( player2 + "-" + to_string(tokens), player1 + "-" + to_string(tokens-1) ) ;

        g_.setEdgeWeight( player1 + "-" + to_string(tokens), player2 + "-" + to_string(tokens-1) , 0 ) ;
        g_.setEdgeWeight( player2 + "-" + to_string(tokens), player1 + "-" + to_string(tokens-1) , 0 ) ;
        continue ;
      }

      g_.insertEdge( player1 + "-" + to_string(tokens), player2 + "-" + to_string(tokens-1) ) ;
      g_.insertEdge( player1 + "-" + to_string(tokens), player2 + "-" + to_string(tokens-2) ) ;

      g_.insertEdge( player2 + "-" + to_string(tokens), player1 + "-" + to_string(tokens-1) ) ;
      g_.insertEdge( player2 + "-" + to_string(tokens), player1 + "-" + to_string(tokens-2) ) ;

      g_.setEdgeWeight( player1 + "-" + to_string(tokens), player2 + "-" + to_string(tokens-1) , 0 ) ;
      g_.setEdgeWeight( player1 + "-" + to_string(tokens), player2 + "-" + to_string(tokens-2) , 0 ) ;

      g_.setEdgeWeight( player2 + "-" + to_string(tokens), player1 + "-" + to_string(tokens-1) , 0 ) ;
      g_.setEdgeWeight( player2 + "-" + to_string(tokens), player1 + "-" + to_string(tokens-2) , 0 ) ;


    }

    // Set the Starting Vertex
    startingVertex_ = player1 + "-" + to_string(startingTokens) ;



}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */

 //srand( time(NULL) ) ;

 Edge path_taken ;
 Vertex current = startingVertex_ ;
 Vertex next ;

 string start_token = startingVertex_ ;
 start_token.erase(0, 3) ;
 int token = stoi(start_token) ;

 int choice ;
 string player = "p2" ;


 while ( current != "p1-0" && current != "p2-0" )
 {
   choice = rand() % 2 + 1 ;

   if ( token == 1 )
     next = player + "-" + to_string(token-1) ;

   else
     next = player + "-" + to_string(token-choice) ;

   path.push_back( g_.getEdge(current, next) ) ;
   current = next ;
   token = token - choice ;

   if ( player == "p2")
    player = "p1" ;

   else
    player = "p2" ;

 }

  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */

  string winner = path.at( int(path.size() - 1) ).source ;
  winner.erase( winner.begin() + 2, winner.end() ) ;

  int weight1 ;
  int weight2 ;
  string player ;

  // Finding out Winner
  if ( winner == "p1" )
  {
    weight1 = 1 ;
    weight2 = -1 ;
  }

  else
  {
    weight1 = -1  ;
    weight2 = 1 ;
  }


  // Setting Edge Weights
  for ( auto it = path.begin() ; it != path.end() ; it++ )
  {
    player = it->source ;
    player.erase( player.begin() + 2, player.end() ) ;

    if ( player == "p1")
      g_.setEdgeWeight(it->source, it->dest, g_.getEdgeWeight(it->source, it->dest) + weight1 );

    else
      g_.setEdgeWeight(it->source, it->dest, g_.getEdgeWeight(it->source, it->dest) + weight2 ) ;
  }


}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
