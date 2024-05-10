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

std::pair<int, int> Converter::GetBorders(
    std::vector<std::pair<double, double>> &XY) {
  std::pair<int, int> minXY{std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max()};
  std::pair<int, int> maxXY{std::numeric_limits<int>::min(),
                            std::numeric_limits<int>::min()};

  for (auto &point : XY) {
    if (point.first < minXY.first) {
      minXY.first = point.first;
    }
    if (point.first > maxXY.first) {
      maxXY.first = point.first;
    }
    if (point.second < minXY.second) {
      minXY.second = point.second;
    }
    if (point.second < minXY.second) {
      minXY.second = point.second;
    }
  }
  int offsetX = minXY.first > 0 ? border_offset : border_offset - minXY.first;
  int offsetY = minXY.second > 0 ? border_offset : border_offset - minXY.second;

  for (auto &point : XY) {
    point.first = std::round(point.first + offsetX);
    point.second = std::round(point.second + offsetY);
  }
  int borderX = std::round(maxXY.first + offsetX + border_offset);
  int borderY = std::round(maxXY.second + offsetY + border_offset);

  borderX += (4 - borderX % 4) % 4;
  return std::pair<int, int>{borderX, borderY};
}

void Converter::prettify_data(std::vector<std::pair<double, double>> &XY) {
  std::pair<int, int> borderXY = GetBorders(XY);
  std::vector<std::vector<int>> vertex_map{borderXY.second,
                                           std::vector{borderXY.first, 255}};
}

void Converter::Convert() {}