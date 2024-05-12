#include "header/Graph.h"

#include <bits/stdc++.h>

#include <iostream>

Graph::Graph(int _order, std::vector<std::vector<int>> _edges)
    : data(_order), distances(_order, std::vector<int>(_order, -1)) {
  order = _order;
  edges.swap(_edges);
  // add symmetric edges to graph
  for (auto edge : edges) {
    data[edge[0]].push_back(edge[1]);
    data[edge[1]].push_back(edge[0]);
  };
  // fill variable distances with data
  FindDist();
  FindDiameter();
};

Graph::Graph(const std::string &filename) {
  std::ifstream input(filename);
  // check if the file opened
  if (!input.is_open()) {
    throw std::runtime_error("Failed to open file");
  }

  input >> order >> size;

  data.resize(order);
  distances.resize(order, std::vector<int>(order, -1));

  for (int i = 0; i < size; i++) {
    int v_from, v_to;
    input >> v_from >> v_to;
    // decrease values, because vector starts from 0
    // we have to do this to make calculations easier
    // and in the graph we restore initial values
    v_from--;
    v_to--;

    // Check if the indices are valid
    if (v_from < 0 || v_to >= order || v_to < 0 || v_to >= order) {
      throw std::runtime_error("Invalid vertex index in edge definition");
    }
    edges.push_back(std::vector<int>{v_from, v_to});

    data[v_from].push_back(v_to);
    data[v_to].push_back(v_from);
  }
  input.close();
  FindDist();
  FindDiameter();
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

void Graph::FindDist() {  // std::vector<std::vector<int>>
  // calling BFS for all verteces
  for (int i = 0; i < order; i++) {
    distances[i] = BFS(i);
  }
};

void Graph::FindDiameter() {
  // max_dist= -1 when all the verteces have no edges
  int max_dist = -1;
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      if (max_dist < Dist(i, j)) {
        max_dist = Dist(i, j);
      }
    }
  }
  diameter = max_dist;
}