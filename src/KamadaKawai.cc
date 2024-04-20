#include "KamadaKawai.h"

#include "Graph.h"

// side - lenght of square area
KamadaKawai::KamadaKawai(Graph graph, int side = 1000, double K = 5)
    : lvect(graph.GetOrder(), std::vector<int>(graph.GetOrder(), -1)),
     kvect(graph.GetOrder(), std::vector<int>(graph.GetOrder(), -1)) {
  int L = side * graph.Diameter();
  for (int i = 0; i < graph.GetOrder(); i++) {
    for (int j = 0; j < graph.GetOrder(); j++) {
      int d = graph.Dist(i, j);
      if (d < 0) {
        continue;
      }
      lvect[i][j] = L * d;
      kvect[i][j] = K / (d ^ 2);
    }
  }
}