#ifndef GRAPH_HEADER_GRAPH_H_
#define GRAPH_HEADER_GRAPH_H_

#include <bits/stdc++.h>

#include <iostream>
#include <vector>

class Graph {
  // Graph order - number of graph vertexes
  int order = 0;
  // all graph edges. Each vector number contains
  // a list with all vertices that are associated with that number.
  std::vector<std::vector<int>> data;

  // contains distances between vertexes.
  // For example: distance[3][2] contains distance between 3 and 2
  // id distances[i][j] == -1 - there is no path.
  // distances[i][i] == 0 always.
  std::vector<std::vector<int>> distances;

  // Breadth-First Search algorithm
  std::vector<int> BFS(int S) const;

  // func to find distances between all of the edges
  std::vector<std::vector<int>> FindDist();

 public:
  // construct graph from edges. If edge {1 , 2}
  // in edges, edges 1-2 and 2-1 aoutomatically added to data.
  explicit Graph(int _order, std::vector<std::vector<int>> &edges);
  // find distance between vertexes using BFS
  int Distance(int _from, int _to) const;
};

#endif  // GRAPH_HEADER_GRAPH_H_