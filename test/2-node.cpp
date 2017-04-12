#include <list>

#include "catch.hpp"
#include "../src/a-star.hpp"

int heuristic(int x, int y) {
    return x + y;
}

TEST_CASE("2 node graph", "[aStar]") {
    int graph[][2] = {{0, 1},{1, 0}};
    int names[] = {0, 1};

    std::list<int> expect;
    expect.push_back(0);
    expect.push_back(1);

    std::list<int> result = aStar(0, 1, names, graph, heuristic);

    REQUIRE(expect.front() == result.front());
    REQUIRE(expect.back()  == result.back() );
}
