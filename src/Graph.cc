#include "Graph.h"
#include <bits/stdc++.h>
#include <iostream>

Graph::Graph(int _order, std::vector<std::vector<int>> &edges){
    order = _order;
    std::vector<std::vector<int>> _data (order);
    for (auto edge : edges) {
        _data[edge[0]].push_back(edge[1]);
        _data[edge[1]].push_back(edge[0]);
    };
    data = _data;
};

std::vector<int> Graph::BFS(int S) {
    // queue to store the nodes in the order they are visited
    std::queue<int> q;
    // vector vith distances from Start Node to other
    std::vector<int> dist(order, -1);
    // Mark the distance of the source node as 0
    dist[S] = 0;
    // Push the source node to the queue
    q.push(S);

    while (!q.empty()) {
        // Pop the node at the front of the queue
        int node = q.front();
        q.pop();

        // Explore all the neighbours of the current node
        for (int neighbour : data[node]) {
            // Check if the neighbouring node is not visited
            if (dist[neighbour] == -1) {
                // // Mark the current node as the parent of
                // // the neighbouring node
                // par[neighbour] = node;

                // Mark the distance of the neighbouring
                // node as distance of the current node + 1
                dist[neighbour] = dist[node] + 1;
                // Insert the neighbouring node to the queue
                q.push(neighbour);
            }
        }
    };
    return dist;
};

int Graph::Distance(int _from, int _to) {
    return BFS(_from)[_to];
}