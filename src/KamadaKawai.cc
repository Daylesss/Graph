#include "KamadaKawai.h"
#define _USE_MATH_DEFINES
#include <cmath>

#include "Graph.h"

// side - lenght of square area
KamadaKawai::KamadaKawai(Graph graph, int side = 1000, double K = 5.0)
    : XY(graph.GetOrder() * graph.GetOrder(), std::pair<int, int>(-1, -1)),
      lvect(graph.GetOrder(), std::vector<double>(graph.GetOrder(), -1)),
      kvect(graph.GetOrder(), std::vector<double>(graph.GetOrder(), -1)) {
  order = graph.GetOrder();
  double L = side / graph.Diameter();
  for (int i = 0; i < graph.GetOrder(); i++) {
    for (int j = 0; j < graph.GetOrder(); j++) {
      double d = graph.Dist(i, j);
      if (d < 0) {
        continue;
      } else if (i == j) {
        continue;
      }
      lvect[i][j] = L * d;
      kvect[i][j] = K / ((d * d) * 1.0);
    }
  }
  InitVertexes(side);
}

void KamadaKawai::InitVertexes(int side) {
  int end = side;
  for (int v = 0; v < order; v++) {
    int x = rand() % (end + 1);
    int y = rand() % (end + 1);
    XY[v] = std::pair<int, int>(x, y);
  }
  // double center = side / 2.0;
  // double angle = M_PI - (M_PI/2.0) * ((order-2.0)/order);
  // XY[0] = std::pair<int, int> (center, 0);
  // for (int v = 1; v < order*order; v++) {
  // }
}

void KamadaKawai::RunOptimization(double eps) {
  while (true) {
    auto m_p = GetMaxM();
    if (m_p.first < eps) {
      break;
    }
    int p = m_p.second;
    while (m_p.first > eps) {
      auto deltaXY = GetDeltaXY(XY[p]);
      XY[p].first = XY[p].first + deltaXY.first;
      XY[p].second = XY[p].second + deltaXY.second;
    }
  }
}

std::pair<double, int> KamadaKawai::GetMaxM() const {
  std::pair<double, int> m_p(-1, -1);
  for (int num = 0; num < order; num++) {
    double m = ComputeM(XY[num]);
    if (m > m_p.first) {
      m_p.first = m;
      m_p.second = num;
    }
  }
  return m_p;
}

double KamadaKawai::ComputeM(std::pair<int, int> p) const {
  double derX = ComputeDer(p.first);
  double derY = ComputeDer(p.second);
  return std::sqrt((std::pow(derX, 2) + std::pow(derY, 2)));
}
