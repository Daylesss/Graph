#include <iostream>
#include <vector>

#include "Graph.h"
#include "KamadaKawai.h"

int main() {
  std::vector<std::vector<int>> edges = {{0, 1}, {1, 2}, {0, 3}, {3, 4},
                                         {4, 7}, {3, 7}, {6, 7}, {4, 5},
                                         {4, 6}, {5, 6}};

  Graph graph{8, edges};
  // std::cout << graph.GetOrder() << graph.Dist(7,6);

  KamadaKawai A{graph, 1000, 5.0};
  std::cout << ">>>>" << A.GetK(0, 6) << " : " << A.GetL(0, 6) << std::endl;
}