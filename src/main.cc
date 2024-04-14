#include <iostream>
#include <vector>
#include "Graph.h"

int main() {
    std::vector<std::vector<int>> edges 
    = { { 0, 1 }, { 1, 2 }, { 0, 3 }, { 3, 4 },
        { 4, 7 }, { 3, 7 }, { 6, 7 }, { 4, 5 },
        { 4, 6 }, { 5, 6 } };
    
    Graph graph {8, edges};
    std::cout << graph.Distance(5, 6) << std::endl;
}