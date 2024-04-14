#ifndef GRAPH_HEADER_GRAPH_H_
#define GRAPH_HEADER_GRAPH_H_

#include <vector>
#include <bits/stdc++.h>
#include <iostream>

class Graph {
    int order = 0;
    std::vector<std::vector<int>> data, distances;


    std::vector<int> BFS(int S);

    public:
        explicit Graph(int _order, std::vector<std::vector<int>> &edges);
        std::vector<std::vector<int>> AllDist(); 

        int Distance(int _from, int _to);
};

#endif // GRAPH_HEADER_GRAPH_H_