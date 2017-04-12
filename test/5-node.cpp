#include <list>

#include "catch.hpp"
#include "../src/a-star.hpp"

// Function determines the flight time in minutes between airports to use as
// the heuristic for a-star
inline int distance(char current, char destination) {
    int dist [5][5] = {
        //a b  c  d  e
        {0, 3, 3, 1, 5}, // a
        {3, 0, 2, 3, 3}, // b
        {3, 2, 0, 2, 4}, // c
        {1, 3, 2, 0, 4}, // d
        {5, 3, 3, 4, 0}  // e
    };
    int c = 0;
    switch (current) {
    case 'a': c = 0; break;
    case 'b': c = 1; break;
    case 'c': c = 2; break;
    case 'd': c = 3; break;
    case 'e': c = 4; break;
    }
    int d = 0;
    switch (destination) {
    case 'a': d = 0; break;
    case 'b': d = 1; break;
    case 'c': d = 2; break;
    case 'd': d = 3; break;
    case 'e': d = 4; break;
    }
    return dist[c][d];
}

// Define vector of vertex names which correspond to matrix row and column
// labels
static const char names[] = {'a','b','c','d','e'};

// Define graph as adjacency matrix wich also stores associated costs
static const int cost[][5] = {
    //a b  c  d  e
    {0, 0, 3, 4, 1}, // a
    {2, 0, 2, 3, 1}, // b
    {0, 1, 0, 1, 0}, // c
    {4, 0, 1, 0, 1}, // d
    {1, 1, 0, 0, 0}  // e
};

TEST_CASE("5 node graph", "[astar]") {

    SECTION("Find otpimal path a->b, expect a->e->b") {
        char s = 'a';
        char g = 'b';
        std::list<char> path = aStar<char, int>(s, g, names, cost, distance);
        int S = 3;
        // Check to see if result path is equal to expected path
        char expect[S] = {'a','e','b'};
        auto v = path.cbegin();
        for(int n = 0; v != path.cend() && n < S; ++v, ++n)
        {
            REQUIRE(*v == expect[n]);
        }
    }
    SECTION("Find optimal path e->a, expect e->a") {
        char s = 'e';
        char g = 'a';
        std::list<char> path = aStar<char, int>(s, g, names, cost, distance);
        int S = 2; char expect[S] = {'e','a'};
        auto v = path.cbegin();
        for(int n = 0; v != path.cend() && n < S; ++v, ++n)
        {
            REQUIRE(*v == expect[n]);
        }
    }
    SECTION("Find optimal path c->a, expect c->b->a") {
        char s = 'c';
        char g = 'a';
        std::list<char> path = aStar<char, int>(s, g, names, cost, distance);
        int S = 3; char expect[S] = {'c','b','a'};
        auto v = path.cbegin();
        for(int n = 0; v != path.cend() && n < S; ++v, ++n)
        {
            REQUIRE(*v == expect[n]);
        }
    }
}
