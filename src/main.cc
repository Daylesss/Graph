#include <time.h>

#include <iostream>
#include <vector>

#include "header/Converter.h"
#include "header/Graph.h"
#include "header/KamadaKawai.h"

int main() {
  std::srand(std::time(0));
  std::vector<std::vector<int>> edges = {{0, 1}, {1, 2}, {0, 3}, {3, 4},
                                         {4, 7}, {3, 7}, {6, 7}, {4, 5},
                                         {4, 6}, {5, 6}};
  Graph graph{8, edges};

  KamadaKawai A{graph, 1000, 5.0};
  A.RunOptimization(0.5);
  Converter C{edges, A.GetVertexPositions()};
  C.Convert("GRAPH.bmp");
}