#pragma once

/*

A* graph search finds the optimal path from some start node in a weighted
digraph to an end node provided such a path exists. A* uses a priority queue to
ensure the algorithm first searches elements which minimize the traversal cost
to the curent node and the value of a heurisic which estimates the future cost
from the current node to the destination.

This implementation uses an adjacency matrix to represent a digraph, however,
which works best in cases where the adjacency matrix is dense meaning each node
in the digraph is connected to many other nodes in the graph.

 */

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <utility>

#include "a-star.cpp"

/*  # aStar
 *
 *  aStar searches for the optimal path through a weighted directed graph from
 *  some start node to some goal node with the assumption that a path exists to
 *  connect them.
 *
 *  ## Template Parameters:
 *  - `Node`: the vertex type
 *  - `Cost`: a numerical type representing the cost that supports weak ordering
 *      and strong equality with 0, prefer integral types
 *  - `size_t N`: the size of the graph to search through
 *
 *  ## Parameters:
 *  - `const Node &START`: the start node, where the graph search starts from
 *  - `const Node &GOAL`: the node to search for in the graph following the
 *      optimal path to reach it.
 *  - `const Node vertex[N]`: an array of vertecies where vertex[n] is the node
 *      value associated with index n
 *  - `const Cost graph[N][N]`: an adjacency matrix where graph[a][b] represents
 *      the traversal cost from a -> b, or contains a zero if no edge exists.
 *      graph[n][] is an adjacency list for a given vertex where graph[a][b] is
 *      the cost of traversal from vertex[a] to vertex[b]
 *  - `Cost (*heuristic)(Node current, Node goal)`: the estimated cost of
 *      traveling from one node to another, prefer under-estimating the cost to
 *      find the optimal path.
 *      Note: In path-finding, an example cost is the distance along the path
 *      from a given node to the start node, and the heuristic is the euclidan
 *      distance from the current node to the end
 *
 *  ## Return values:
 *      A `list` of nodes from the start to the goal assuming a goal was
 *      in fact discovered.
 *
 *  ## Known failure conditions and edge case behaviour:
 *  Improper heuristic: if the heuristic does not appropriately estimate the
 *      cost from the current node to the goal node, the search can get stuck in
 *      a loop where it cycles between a few elements.
 *
 *  If the START and GOAL node are the same, rather than finding the most
 *      efficient round-trip, aStar will just return the same node; this may
 *      differ from desired behaviour.
 *
 *  Behaviour is undefined if Cost or Heuristic values are negative.
 *
 *  ## Performance
 *  In the worst case, A* has exponential time complexity; however, in practice
 *  with a good heuristic, A* will converge linearly with polynomial time
 *  complexity.
 */
template<typename Node, typename Cost, size_t N>
std::list<Node> aStar(
    const Node &START,
    const Node &GOAL,
    const Node vertex[N],
    const Cost graph[N][N],
    Cost (*heuristic)(Node current,Node goal));
