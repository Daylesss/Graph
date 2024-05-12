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

  int order = 0;

  // set random values of cordinates for the verteces
  void InitVerteces(int side);

  // return pair of number of vertex with maximum
  // deviation and the deviation value
  std::pair<double, int> GetMaxM();

  // compute the deviation using the formula
  double ComputeM(int num);

  // compute first degree derivatives for coordinates
  // of the passed vertex
  std::pair<double, double> ComputeDer(int num);

  // get displacement for x and y
  // to minimize deviation
  std::pair<double, double> GetDeltaXY(int num);

  // compute derivate by y and x variables
  double ComputeA12(int num);

  // compute second degree derivatives for coordinates
  // of the passed vertex
  std::pair<double, double> Compute2Der(int num);

 public:
  // init verteces by setting cordinates
  // Compute all l and k for all verteces
  explicit KamadaKawai(Graph &graph, int side, double K);

  // main loop for algorith
  // move verteces into positions with low energy
  // until desired until maximum deviation (MaxM)
  // will be smaller than eps
  void RunOptimization(double eps);
  // Get L for spring. l - desired lenght of the spring
  double GetL(int _from, int _to) { return lvect[_from][_to]; };
  // Get K for spring. k - is an multiplier of spring to compuste energy
  // k*d/2 - energy of the spring
  double GetK(int _from, int _to) { return kvect[_from][_to]; };
  // return coordinates of the 'i' vertex
  auto GetXY(int num) { return XY[num]; };
  // return all coordinates
  auto GetVertexPositions() { return XY; };
};

#endif  // GRAPH_HEADER_VISUALIZER_H_
