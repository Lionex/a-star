#pragma once

/*

A* graph search finds the optimal path from some start node in a weighted digraph to an end node provided such a path exists. A* uses a priority queue to ensure the algorithm first searches elements which minimize the traversal cost to the curent node and the value of a heurisic which estimates the future cost from the current node to the destination.

This implementation uses an adjacency matrix to represent a digraph, however, which works best in cases where the adjacency matrix is dense meaning each node in the digraph is connected to many other nodes in the graph.

 */

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <utility>

#include "a-star.cpp"

template<typename Node, typename Cost>
bool contains(std::deque<Node> queue, Node node);

template<typename Node, typename Cost, size_t N>
size_t index_of(Node node, Node nodes[N]);


/*

 */
template<typename Node, typename Cost, size_t N>
std::list<Node> aStar(
    const Node &START,
    const Node &GOAL,
    const Node vertex[N],
    const Cost graph[N][N],
    Cost (*heuristic)(Node current,Node goal));
