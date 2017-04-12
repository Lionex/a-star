#pragma once

#include "a-star.hpp"

template<typename T>
bool contains(std::deque<T> queue, T node) {
    for (auto item : queue) {
        if (item == node) {
            return true;
        } else {return false;}
    }
}

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
    // Set of discovered but unevaluated nodes starting from the start node
    typedef std::pair<Cost, size_t> El;
    std::priority_queue<El, std::vector<El>, std::greater<El>> frontier;
    frontier.emplace(0, index_of<Node, N>(START, vertex));
    // Set of evaluated nodes
    std::deque<size_t> explored;

    // The most efficient neighbor for each vertex
    std::unordered_map<size_t, size_t> parent;
    // Cost value of each vertex
    std::unordered_map<size_t, Cost> aggregateCost;
    aggregateCost[frontier.top().second] = 0;

    size_t current;
    // Continue the earch for optimal path as long as open nodes exist
    while (!frontier.empty()) {
        current = frontier.top().second;
        // Break early algorithm arrived at the goal
        if (vertex[current] == GOAL) {break;}

        // Mark current node as explored
        explored.push_front(frontier.top().second);
        frontier.pop();

        for (size_t n = 0; n < N; n++) {
            if (graph[current][n] == 0) {continue;}
            Cost cost = aggregateCost[current] + graph[current][n];
            if (!contains(explored, n) || cost < aggregateCost[n]) {
                parent[n] = current;
                aggregateCost[n] = cost;
                frontier.emplace(cost + heuristic(vertex[n], GOAL), n);
            }
        }
    }

    std::list<Node> path;
    path.push_front(vertex[current]);
     while (vertex[current] != START) {
        path.push_front(vertex[parent[current]]);
        current = parent[current];
    }
    return path;
}
