#pragma once

#include "a-star.hpp"

// Find an item by value in a Deque and return true if it is found, utility
template<typename T>
bool contains(std::deque<T> queue, T node) {
    for (auto item : queue) {
        if (item == node) {
            return true;
        } else {return false;}
    }
}

// Assuming an array contains a given value, find the index of it's first
// appearance
template<typename Node, size_t N>
size_t index_of(Node node, const Node nodes[N]) {
    for (size_t n = 0; n < N; n++) {
        if (nodes[n] == node) {return n;}
    }
}

template<typename Node, typename Cost, size_t N>
std::list<Node> aStar
    (const Node &START,
    const Node &GOAL, const Node vertex[N],
    const Cost graph[N][N],
    Cost (*heuristic)(Node current, Node goal))
{
    // Priority queue: discovered but unevaluated nodes starting from the start
    // The priority is the heuristic + cost thus prioritizing the most efficient
    // neighbour by placing it at the top of the queue
    typedef std::pair<Cost, size_t> El;
    std::priority_queue<El, std::vector<El>, std::greater<El>> frontier;
    frontier.emplace(0, index_of<Node, N>(START, vertex));
    // Set of evaluated nodes to prevent unecessary duplicate exploration
    std::deque<size_t> explored;

    // The most efficient neighbor for each vertex so we have a way to
    // reconstruct the most efficient path by "unwinding" parents
    std::unordered_map<size_t, size_t> parent;
    // Cost value of each vertex
    std::unordered_map<size_t, Cost> aggregateCost;
    aggregateCost[frontier.top().second] = 0;

    size_t current;
    // Continue the earch for optimal path as long as open nodes exist
    while (!frontier.empty()) {
        current = frontier.top().second;
        if (vertex[current] == GOAL) {break;}

        explored.push_front(frontier.top().second);
        frontier.pop();

        // Search neighbours and evaluate the cost, using the cost + heuristic
        // to insert the values in a priority queue so the most efficient
        // neighbours are explored first to find the optimal path.
        for (size_t n = 0; n < N; n++) {
            // Skip if the adjacency matrix indicates no edge exists
            if (graph[current][n] == 0) {continue;}
            // Determine the cost accrued traversing the graph up to the
            // discovered neighbour
            Cost cost = aggregateCost[current] + graph[current][n];
            if (!contains(explored, n) || cost < aggregateCost[n]) {
                parent[n] = current;
                aggregateCost[n] = cost;
                frontier.emplace(cost + heuristic(vertex[n], GOAL), n);
            }
        }
    }

    // Unwind the most efficient parents for each node to construct optimal path
    std::list<Node> path;
    path.push_front(vertex[current]);
     while (vertex[current] != START) {
        path.push_front(vertex[parent[current]]);
        current = parent[current];
    }
    return path;
}
