#include <iostream>

#include <list>
#include "../src/a-star.hpp"

enum Airport {
    LAX=0, MIA=1, ATL=2, DEN=3, JFK=4
};

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

// Flight time in minutes between airports, forms a basis for the heuristic
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

    // Define vector of vertex names which correspond to matrix row and column
    // labels
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

    Airport start = LAX;
    Airport destination = MIA;
    std::list<Airport> route = aStar<Airport, Dollars>(start, destination, names, routes, flight_time);

    std::cout << "Cheapest route";
    for (auto stop : route) {
        std::cout << " -> " << stop;
    }
}
