#include "header/KamadaKawai.h"
#define _USE_MATH_DEFINES
#include <cmath>

#include "header/Graph.h"

// side - lenght of square area
KamadaKawai::KamadaKawai(Graph &graph, int side = 1000, double K = 5.0)
    : XY(graph.GetOrder(), std::pair<int, int>(-1, -1)),
      lvect(graph.GetOrder(), std::vector<double>(graph.GetOrder(), -1)),
      kvect(graph.GetOrder(), std::vector<double>(graph.GetOrder(), -1)) {
  // _graph = graph;
  order = graph.GetOrder();
  double L = side / graph.GetDiameter();
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      double d = graph.Dist(i, j);
      if (d < 0) {
        continue;
      } else if (i == j) {
        continue;
      }
      lvect[i][j] = L * d * 1.0;
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
    while (true) {
      double a = ComputeM(p);
      // std::cout << ">> " << a <<std::endl;
      if (a < eps) {
        break;
      }
      auto deltaXY = GetDeltaXY(p);
      XY[p].first = XY[p].first + deltaXY.first;
      XY[p].second = XY[p].second + deltaXY.second;
    }
  }
}

std::pair<double, int> KamadaKawai::GetMaxM() {
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

double KamadaKawai::ComputeM(int num) {
  std::pair<double, double> derXY = ComputeDer(num);
  return std::sqrt(std::pow(derXY.first, 2) + std::pow(derXY.second, 2));
}

std::pair<double, double> KamadaKawai::ComputeDer(int num) {
  double sumX = 0;
  double sumY = 0;
  for (int i = 0; i < order; i++) {
    if (i == num) {
      continue;
    }
    // if (graph.Dist(num, i) == -1) {continue;}
    double deltaX = (XY[num].first - XY[i].first);
    double deltaY = (XY[num].second - XY[i].second);
    double denominator = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));

    double fracX = (GetL(num, i) * deltaX) / denominator;
    sumX += GetK(num, i) * (deltaX - fracX);

    double fracY = (GetL(num, i) * deltaY) / denominator;
    sumY += GetK(num, i) * (deltaY - fracY);
  }
  return std::pair<double, double>(sumX, sumY);
}

std::pair<double, double> KamadaKawai::GetDeltaXY(int num) {
  std::pair<double, double> derXY = ComputeDer(num);
  std::pair<double, double> a1_b2 = Compute2Der(num);
  double c1 = -derXY.first;
  double c2 = -derXY.second;
  double b1 = ComputeA12(num);
  double a2 = b1;
  double a1 = a1_b2.first;
  double b2 = a1_b2.second;

  double determ = a2 * b1 - b2 * a1;
  double deltaX = (c2 * b1 - b2 * c1) / determ;
  double deltaY = (c1 * a2 - c2 * a1) / determ;
  return std::pair<double, double>(deltaX, deltaY);
}

double KamadaKawai::ComputeA12(int num) {
  double sum = 0.0;
  for (int i = 0; i < order; i++) {
    if (i == num) {
      continue;
    }
    double deltaX = XY[num].first - XY[i].first;
    double deltaY = XY[num].second - XY[i].second;
    double denum = std::pow(deltaX, 2) + std::pow(deltaY, 2);
    denum = denum * std::sqrt(denum);
    sum += GetK(num, i) * (GetL(num, i) * deltaX * deltaY) / denum;
  }
  return sum;
}

std::pair<double, double> KamadaKawai::Compute2Der(int num) {
  double sumX = 0.0;
  double sumY = 0.0;
  for (int i = 0; i < order; i++) {
    if (i == num) {
      continue;
    }
    double deltaX = XY[num].first - XY[i].first;
    double deltaY = XY[num].second - XY[i].second;
    double denum = std::pow(deltaX, 2) + std::pow(deltaY, 2);
    denum = denum * std::sqrt(denum);
    double numX = GetL(num, i) * std::pow(deltaY, 2);
    double numY = GetL(num, i) * std::pow(deltaX, 2);

    sumX += GetK(num, i) * (1 - numX / denum);
    sumY += GetK(num, i) * (1 - numY / denum);
  }
  return std::pair<double, double>(sumX, sumY);
}