#include "KamadaKawai.h"

#include "Graph.h"

// side - lenght of square area
KamadaKawai::KamadaKawai(Graph graph, int side = 1000, double K = 5)
    : XY(graph.GetOrder()), lvect(graph.GetOrder()), kvect(graph.GetOrder()) {
  int L = side * graph.Diameter();
  for (int i = 0; i < graph.GetOrder(); i++) {
    for (int j = 0; j < graph.GetOrder(); j++) {
      lvect[i][j] = L * graph.Dist(i, j);
      kvect[i][j] = K / (graph.Dist(i, j) ^ 2);
    }
  }
}