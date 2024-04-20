#include "header/Graph.h"

#include <bits/stdc++.h>

#include <iostream>

Graph::Graph(int _order, std::vector<std::vector<int>> &edges)
    : data(_order), distances(_order) {
  order = _order;
  // add symmetric edges to graph
  for (auto edge : edges) {
    data[edge[0]].push_back(edge[1]);
    data[edge[1]].push_back(edge[0]);
  };

  distances = FindDist();
};

std::vector<int> Graph::BFS(int S) const {
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

std::vector<std::vector<int>> Graph::FindDist() {
  // calling BFS for all vertexes
  for (int i = 0; i < order; i++) {
    std::vector<int> dist = BFS(i);
    distances[i] = dist;
  }
  return distances;
};

int Graph::Dist(int _from, int _to) const { return distances[_from][_to]; }

int Graph::Diameter() const {
  int max_dist = -1;
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      if (max_dist < Dist(i, j)) {
        max_dist = Dist(i, j);
      }
    }
  }
  return max_dist;
}

int Graph::GetOrder() const { return order; }