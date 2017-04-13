# Example: Cheapest Flights

[Back to Quick Start](index.html)

This exmaple hopes to determine the cheapest route from one airport to another using the flight time as a heuristic.

Finding flight routes are a good case for adjacency matrix digraphs because they tend to be dense (it's possible to fly from nearly any airport to any other airport), making them memory efficient.

A-star finds the cheapest route by exploring all of the neighbour airports to find the airport with the lowest flight time to the destination and lowset Cost from the departure airport until it finds the cheapest path.

We can start by simply including the header file along with some some standard library files:
```cpp
#include <assert.h>
#include <iostream>
#include <list>

#include "a-star.hpp"
```

Next we need some data types: a simple enum for `Airport`s works
well as our vertex/node type to start.  To keep things simple we'll work with just five `Airport`s.

```cpp
enum Airport { LAX, MIA, ATL, DEN, JFK };

// Implement stream insertion operator for pretty printing
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
```

Next we need a type to use in our cost matrix, aliasing `int` as our own `Dollars` type works well enough.

```cpp
using Dollars = int;
```

Now comes the real work: building our graph.  We start with an array of vertex names which correspond to the row and column labels for our adjacency matrix.  Following the order in the enum is just fine.

```cpp
const Airport names[] = {LAX, MIA, ATL, DEN, JFK};
```

Now we must define an adjacency matrix where flights from each row airport to each column airport correspond to an edge with the associated cost in Dollars.  I purposefully construced the matrix so that a direct flight from `LAX` to `MIA` is more expensive than connecting through `ATL` so we could have a simple test case to work with.

```cpp
const Dollars routes[][5] = {
    //LAX MIA  ATL  DEN  JFK
    {  0, 500, 200, 136, 299}, // LAX
    {438,   0, 114, 330, 247}, // MIA
    {204, 104,   0, 199, 205}, // ATL
    {116, 300, 164,   0, 247}, // DEN
    {275, 230, 198, 212,   0}  // JFK
};
```
Following the indecies in the matrix, `LAX -> MIA` costs $500, but `LAX -> ATL -> MIA` costs just $404 by comparison.

Next we need a heuristic; I used flight time in minutes because the magnitude is comparable to the cost.  In other cases I advise using the same units if possible. *Note*: it's often appropriate to inline the heuristic function.

```cpp
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

    // Use the fact that enumerated types work like ints to easily index matrix
    return times[current][destination];
}
```

Now we have all of our data and we have a heuristic, so we are ready to search!

```cpp
std::list<Airport> route = aStar<Airport, Dollars>(LAX, MIA, names, routes, flight_time);
```

All that's left is to compare the results to make sure our assumptions held!

```cpp
char expect[] = {LAX,ATL,MIA};
auto v = path.cbegin();
for(int n = 0; v != path.cend() && n < 3; ++v, ++n)
{
    assert(*v == expect[n]);
}
```
