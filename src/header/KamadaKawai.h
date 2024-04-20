#ifndef GRAPH_HEADER_VISUALIZER_H_
#define GRAPH_HEADER_VISUALIZER_H_
#include <iostream>
#include <utility>
#include <vector>

#include "Graph.h"

class KamadaKawai {
  // vector of vertex cordinates
  std::vector<std::pair<int, int>> XY;

  // all desired lenghts of springs
  std::vector<std::vector<int>> lvect;

  // all spring ratios
  std::vector<std::vector<int>> kvect;

  // // constant to compute l
  // int L = 0;
  // // Get L for spring. l - desired lenght of the spring
  // int SprL(int dist) const;
  // // Get K for spring. k - is an multiplier of spring to compuste energy
  // // k*d/2 - energy of the spring
  // int SprK(int dist) const;

 public:
  explicit KamadaKawai(Graph graph, int side, double K);
  
  int GetL(int _from, int _to) const {return lvect[_from][_to];};
  int GetK(int _from, int _to) const {return kvect[_from][_to];};
};

#endif  // GRAPH_HEADER_VISUALIZER_H_
