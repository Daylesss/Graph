#include "KamadaKawai.h"
#define _USE_MATH_DEFINES
#include <cmath>

#include "Graph.h"

// side - lenght of square area
KamadaKawai::KamadaKawai(Graph &graph, int side = 1000, double K = 5.0)
    : XY(graph.GetOrder() * graph.GetOrder(), std::pair<int, int>(-1, -1)),
      lvect(graph.GetOrder(), std::vector<double>(graph.GetOrder(), -1)),
      kvect(graph.GetOrder(), std::vector<double>(graph.GetOrder(), -1)) {
  _graph = graph;
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
    double m = ComputeM(num);
    if (m > m_p.first) {
      m_p.first = m;
      m_p.second = num;
    }
  }
  return m_p;
}

double KamadaKawai::ComputeM(int num) const {
  std::pair<double, double> derXY = ComputeDer(num);
  return std::sqrt((std::pow(derXY.first, 2) + std::pow(derXY.second, 2)));
}

std::pair<double, double> KamadaKawai::ComputeDer(int num) const {
  double sumX = 0;
  double sumY = 0;
  for (int i=0; i < order; i++) {
    if (i == num) {continue;}
    // if (graph.Dist(num, i) == -1) {continue;}
    double deltaX = (XY[num].first - XY[i].first);
    double deltaY = (XY[num].second - XY[i].second);
    double denominator = std::sqrt(std::pow(deltaX, 2) - std::pow(deltaY, 2));

    double fracX = (GetL(num, i) * deltaX)/denominator;
    sumX += GetK(num, i) * (deltaX - fracX);

    double fracY = (GetL(num, i) * deltaY) / denominator;
    sumY +=  GetK(num, i) * (deltaY - fracY);
  return std::pair<double, double> (sumX, sumY);
  }
}