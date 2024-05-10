#include <time.h>

#include <iostream>
#include <vector>

#include "header/Converter.h"
#include "header/Graph.h"
#include "header/KamadaKawai.h"

void test(std::vector<std::pair<int, int>> &A) {
  for (auto &a : A) {
    a.first = 1;
  }
}

int main() {
  std::srand(std::time(0));
  std::vector<std::vector<int>> edges = {{0, 1}, {1, 2}, {0, 3}, {3, 4},
                                         {4, 7}, {3, 7}, {6, 7}, {4, 5},
                                         {4, 6}, {5, 6}};

  Graph graph{8, edges};
  // // std::cout << graph.GetOrder() << graph.Dist(7,6);

  KamadaKawai A{graph, 1000, 5.0};
  A.RunOptimization(0.5);
  // std::vector<std::vector<int>> d{std::vector<int>(1)};
  // std::vector<std::pair<double, double>> XY{
  //     std::pair<double, double>(-23.64, 5)};
  Converter C{A.GetVertexPositions(), "TEST.bmp"};
  // auto xy = A.GetXY(4);
  // std::cout << xy.first << " : " << xy.second << std::endl;
}