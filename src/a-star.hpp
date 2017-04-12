#pragma once

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <vector>
#include <utility>

#include "a-star.cpp"

template<typename Node, typename Cost>
bool contains(std::deque<Node> queue, Node node);

template<typename Node, typename Cost, size_t N>
size_t index_of(Node node, Node nodes[N]);

template<typename Node, typename Cost, size_t N>
std::list<Node> aStar(
    const Node &START,
    const Node &GOAL,
    const Node vertex[N],
    const Cost graph[N][N],
    Cost (*heuristic)(Node current,Node goal));
