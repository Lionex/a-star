# A* graph search Quick Start

[![Build Status](https://travis-ci.org/Lionex/a-star.svg?branch=master)](https://travis-ci.org/Lionex/a-star)

[Get the source code on GitHub.](htps://github.com/Lionex/a-star)

A\* graph search finds the optimal path from some start node in a weighted digraph to an end node provided such a path exists.  A\* uses a priority queue to ensure the algorithm first searches elements which minimize the traversal cost to the curent node and the value of a heurisic which estimates the future cost from the current node to the destination.

A\* appears most commonly in path-finding applications to search for a path through a navigation mesh or coordinate grid passed obstacles on the grid which must be passed.  However, A\* also works just as well on any weighted directed graph where it's possible to determine the cost to the current node and the approximate cost from the current node to the destination.

This implementation uses an adjacency matrix to represent a digraph, however, which works best in cases where the adjacency matrix is dense meaning each node in the digraph is connected to many other nodes in the graph.

## Minimal Example

To get started simply download the header and cpp files and `#include "a-star.hpp"`.

```cpp
#include <assert.h>
#include <list>

#include "a-star.hpp"

```

For the graph search to work we need to define a simple heuristic that returns something akin to the manhattan distance.

```cpp
int heuristic(int x, int y) {
    return x + y;
}
```

Next we must define the weighted directed graph to search through.  As a minimal example, we can have a simple graph `a <---> b` with a uniform weight of `1` on each edge.

```cpp
char names[] = {'a', 'b'};
int graph[][2] = {
//   a  b
    {0, 1},// from a
    {1, 0} // from b
};
```

Once we have all of our data, we can perform the search!

```cpp
std::list<char> result = aStar('a', 'b', names, graph, heuristic);
```

We expect the optimal path to be `a -> b`, since there is no other possibility.  That makes the outcome simple to test for this minimal example.

```cpp
std::list<char> expect;
expect.push_back('a');
expect.push_back('b');

assert(expect.front() == result.front());
assert(expect.back()  == result.back() );
```

# References

1. [Introduction to A\*](http://www.redblobgames.com/pathfinding/a-star/introduction.html), includes many useful interactive diagrams and visualizations building from depth-first-search to A\*
2. [A\* implementation](http://www.redblobgames.com/pathfinding/a-star/implementation.html) shows implementation samples in a host of languages
3. [Data structure comparison](http://theory.stanford.edu/~amitp/GameProgramming/ImplementationNotes.html) contains an in-depth discussion of various different data structures that can be used to implement A\*, comparing their speed in terms of adding and removing elements, accessing elements, and finding elements.


# Building documentation

Ensure that `sphynx` and `recommonmark` have been installed, then enter the `docs\` directory and run `make [target]`; for a list of targets just run `make`.

To install `sphynx` and `recommonmark` run:

```
$ pip install sphinx sphinx-autobuild
$ pip install recommonmark
```
# License
**Copyright © 2017 \<Gwen Lofman\>**

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
