#ifndef GRAPH_HEADER_VISUALIZER_H_
#define GRAPH_HEADER_VISUALIZER_H_
#include <iostream>
#include <utility>
#include <vector>

#include "Graph.h"

class KamadaKawai {
  // vector of vertex cordinates
  std::vector<std::pair<double, double>> XY;

  // all desired lenghts of springs
  std::vector<std::vector<double>> lvect;

  // all spring ratios
  std::vector<std::vector<double>> kvect;

  // // constant to compute l
  // int L = 0;
  // // Get L for spring. l - desired lenght of the spring
  // int SprL(int dist) const;
  // // Get K for spring. k - is an multiplier of spring to compuste energy
  // // k*d/2 - energy of the spring
  // int SprK(int dist) const;

  void InitVertexes(int side, int order);

 public:
  explicit KamadaKawai(Graph graph, int side, double K);

  void RunOptimization();

  double GetL(int _from, int _to) const { return lvect[_from][_to]; };
  double GetK(int _from, int _to) const { return kvect[_from][_to]; };
  auto GetXY(int num) const { return XY[num]; }
};

#endif  // GRAPH_HEADER_VISUALIZER_H_
