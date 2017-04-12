#include <iostream>

#include <list>
#include "../src/a-star.hpp"

/*

# Airport Example:

This exmaple hopes to determine the cheapest route from one airport to another
using the flight time as a heuristic.

Finding flight routes are a good case for adjacency matrix digraphs because they
tend to be dense (it's possible to fly from nearly any airport to any other
airport), making them memory efficient.

A-star finds the cheapest route by exploring all of the neighbour airports to
find the airport with the lowest flight time to the destination and lowset Cost
from the start until it finds the optimal path.

 */

enum Airport { LAX, MIA, ATL, DEN, JFK };

// Define stream insertion for pretty printing
std::ostream& operator<<(std::ostream& os, const Airport& a) {
    std::string out;
    switch (a) {
    case LAX: out = "LAX"; break;
    case MIA: out = "MIA"; break;
    case ATL: out = "ATL"; break;
    case DEN: out = "DEN"; break;
    case JFK: out = "JFK"; break;
    }
    return os << out;
}

using Dollars = double;

// Flight time in minutes between airports to use as heuristic for A*
inline Dollars flight_time(Airport current, Airport destination) {
    Dollars times [5][5] = {
        //LAX   MIA   ATL   DEN   JFK
        {   0, 4*60, 3*60, 1*60, 5*60}, // LAX
        {4*60,    0, 1*60, 4*60, 3*60}, // MIA
        {3*60, 2*60,    0, 2*60, 4*60}, // ATL
        {1*60, 4*60, 2*60,    0, 4*60}, // DEN
        {5*60, 3*60, 3*60, 4*60,    0}  // JFK
    };

    return times[current][destination];
}

int main() {

    // Define vertex names which correspond to matrix row and column    // labels
    const Airport names[] = {LAX, MIA, ATL, DEN, JFK};

    // Define adjacency matrix where flights from each row airport to each
    // column airport correspond to an edge with the associated cost
    const Dollars routes[][5] = {
        //LAX MIA  ATL  DEN  JFK
        {  0, 500, 200, 136, 299}, // LAX
        {438,   0, 114, 330, 247}, // MIA
        {204, 104,   0, 199, 205}, // ATL
        {116, 300, 164,   0, 247}, // DEN
        {275, 230, 198, 212,   0}  // JFK
    };

    std::list<Airport> route = aStar<Airport, Dollars>(LAX, MIA, names, routes, flight_time);

    std::cout << "Cheapest route, expect LAX -> ATL -> MIA,\nfound ";
    for (auto stop : route) {
        std::cout << " -> " << stop;
    }
}
