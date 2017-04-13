# API documentation

[Back to Quick Start](index.html)

`aStar` searches for the optimal path through a weighted directed graph from
some start node to some goal node with the assumption that a path exists to
connect them.

```cpp
template<typename Node, typename Cost, size_t N>
std::list<Node> aStar(
    const Node &amp;START,
    const Node &amp;GOAL,
    const Node vertex[N],
    const Cost graph[N][N],
    Cost (*heuristic)(Node current,Node goal));
```

## Template Parameters:

- `Node`: the vertex type
- `Cost`: a numerical type representing the cost that supports weak ordering
    and strong equality with 0, prefer integral types
- `size_t N`: the size of the graph to search through

## Parameters:

- `const Node &START`: the start node, where the graph search starts from
- `const Node &GOAL`: the node to search for in the graph following the
    optimal path to reach it.
- `const Node vertex[N]`: an array of vertecies where `vertex[n]` is the node
    value associated with index `n`
- `const Cost graph[N][N]`: an adjacency matrix where `graph[a][b]` represents
    the traversal cost from a -> b, or contains a zero if no edge exists.
    `graph[n]` is an adjacency list for a given vertex where `graph[a][b]` is
    the cost of traversal from `vertex[a]` to `vertex[b]`
- `Cost (*heuristic)(Node current, Node goal)`: the estimated cost of
    traveling from one node to another, prefer under-estimating the cost to
    find the optimal path.
    Note: In path-finding, an example cost is the distance along the path
    from a given node to the start node, and the heuristic is the euclidan
    distance from the current node to the end

## Return values:

A `list` of nodes from the start to the goal assuming a goal was
in fact discovered.


## Failure conditions & undefined behaviour

If the heuristic does not appropriately estimate the cost from the current node to the goal node, the search can get stuck in a loop where it cycles between a few elements. **Behaviour is undefined if Cost or Heuristic values are negative.**

If the START and GOAL node are the same, rather than finding the most efficient round-trip, aStar will just return the same node; this may differ from desired behaviour.

If `START` and `GOAL` nodes are not in `Node vertex[N]`, the search will fail.

If using a floating point type as the `Cost` type, the algorithm cannot properly identify edges that do exist vs edges that don't because `int 0` does is not necessarily equal to `double 0.0`, and the algorithm uses equality to zero to define an edge that doesn't exist.

## Performance
In the worst case, A\* has exponential time complexity; however, in practice with a good heuristic, A* will converge linearly with polynomial time complexity.
