#ifndef GRAPH_HEADER_GRAPH_H_
#define GRAPH_HEADER_GRAPH_H_

#include <bits/stdc++.h>

#include <iostream>
#include <vector>

class Graph {
  // Graph order - number of graph verteces
  int order = 0;
  // number of edges int the graph
  int size = 0;
  // longest path in the graph
  int diameter = 0;
  // all graph edges. Each vector number contains
  // a list with all vertices that are associated with that number.
  std::vector<std::vector<int>> data;

  // edges (without doubles)
  std::vector<std::vector<int>> edges;

  // contains distances between verteces.
  // For example: distance[3][2] contains distance between 3 and 2
  // id distances[i][j] == -1 - there is no path.
  // distances[i][i] == 0 always.
  std::vector<std::vector<int>> distances;

  // Breadth-First Search algorithm
  std::vector<int> BFS(int S) const;

  // func to find distances between all of the edges
  //  using BFS
  void FindDist();
  // find the longest distance in the graph
  void FindDiameter();

 public:
  // construct graph from edges. If edge {1 , 2}
  // in edges, edges 1-2 and 2-1 aoutomatically added to data.
  explicit Graph(int _order, std::vector<std::vector<int>> _edges);
  explicit Graph(const std::string &filename);
  // get distance between verteces
  int Dist(int _from, int _to) const { return distances[_from][_to]; };
  // return the number of verteces
  int GetOrder() const { return order; };
  // return the longest path between vertexes in the graph
  int GetDiameter() const { return diameter; }
  // return all edges passed during initializing
  std::vector<std::vector<int>> GetEdges() const {return edges;}
};

#endif  // GRAPH_HEADER_GRAPH_H_