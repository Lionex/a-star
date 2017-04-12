# A* graph search

[![Build Status](https://travis-ci.org/Lionex/a-star.svg?branch=master)](https://travis-ci.org/Lionex/a-star)

A\* graph search finds the optimal path from some start node in a weighted digraph to an end node provided such a path exists.  A\* uses a priority queue to ensure the algorithm first searches elements which minimize the traversal cost to the curent node and the value of a heurisic which estimates the future cost from the current node to the destination.

A\* appears most commonly in path-finding applications to search for a path through a navigation mesh or coordinate grid passed obstacles on the grid which must be passed.  However, A\* also works just as well on any weighted directed graph where it's possible to determine the cost to the current node and the approximate cost from the current node to the destination.

This implementation uses an adjacency matrix to represent a digraph, however, which works best in cases where the adjacency matrix is dense meaning each node in the digraph is connected to many other nodes in the graph.

## Quick Start

To get started simply download the header and cpp files and `#include "a-star.hpp"`.

```cpp
#include <assert.h>
#include <list>

#include "a-star.hpp"

// Define simple heuristic that returns something akin to the manhattan distance
int heuristic(int x, int y) {
    return x + y;
}


int main() {
    // Minimum example of a two node graph
    int graph[][2] = {{0, 1},{1, 0}};
    int names[] = {0, 1};

    // Find optimal path from node `0` to node `1`
    std::list<int> result = aStar(0, 1, names, graph, heuristic);

    // expected optimal path: {0, 1}
    std::list<int> expect;
    expect.push_back(0);
    expect.push_back(1);

    assert(expect.front() == result.front());
    assert(expect.back()  == result.back() );
}

```
