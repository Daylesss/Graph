#include "header/Converter.h"

#include <cmath>
#include <limits>
#include <vector>

#include "header/Graph.h"

Converter::Converter(
    // std::vector<std::vector<int>>distances,
    std::vector<std::pair<double, double>> XY
    //  int side
) {
  auto &points = XY;
  prettify_data(points);

  //   std::vector<std::vector<>>
}

void Converter::prettify_data(std::vector<std::pair<double, double>> &XY) {
  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max();

  for (auto &point : XY) {
    if (point.first < minX) {
      minX = point.first;
    }
    if (point.second < minY) {
      minY = point.second;
    }
  }
  int offsetX = minX > 0 ? border_offset : border_offset - minX;
  int offsetY = minY > 0 ? border_offset : border_offset - minY;

  for (auto &point : XY) {
    point.first = std::round(point.first + offsetX);
    point.second = std::round(point.second + offsetY);
  }
}

void Converter::Convert() {}