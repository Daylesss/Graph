#ifndef GRAPH_HEADER_VISUALIZER_H_
#define GRAPH_HEADER_VISUALIZER_H_
#include <iostream>
#include <utility>
#include <vector>

#include "Graph.h"

class KamadaKawai {
  // vector of vertex cordinates
  std::vector<std::pair<int, int>> VC;

  // lenght of side of square area
  //  need to compute an L and l
  int side_lenght = 0;
  // constant to compute l
  int L = 0;
  // return max value of nested vectors
  int GetMaxDist() const;
  // Get L for spring. l - desired lenght of the spring
  int SprL(int dist) const;
  // Get K for spring. k - is an multiplier of spring to compuste energy
  // k*d/2 - energy of the spring
  int SprK(int dist) const;

 public:
  explicit KamadaKawai(int order, Graph graph) : VC(order) {}
};

#endif  // GRAPH_HEADER_VISUALIZER_H_
