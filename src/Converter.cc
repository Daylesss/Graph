#include "header/Converter.h"

#include <cmath>
#include <limits>
#include <vector>

#include "header/BMP.h"
#include "header/Graph.h"

Converter::Converter(std::vector<std::vector<int>> edges,
                     std::vector<std::pair<double, double>> XY,
                     const std::string &filename) {
  auto &points = XY;
  ConvertToMap(points, edges);

  BMP graph_img;
  graph_img.Interpret(vertex_map);
  graph_img.Write(filename);
}

void Converter::ComputeBorders(std::vector<std::pair<double, double>> &XY) {
  std::pair<double, double> minXY{std::numeric_limits<double>::max(),
                                  std::numeric_limits<double>::max()};
  std::pair<double, double> maxXY{std::numeric_limits<double>::min(),
                                  std::numeric_limits<double>::min()};

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
    if (point.second > maxXY.second) {
      maxXY.second = point.second;
    }
  }
  // return {1000, 1000};
  double offsetX =
      minXY.first > 0 ? border_offset : border_offset - minXY.first;
  double offsetY =
      minXY.second > 0 ? border_offset : border_offset - minXY.second;

  for (auto &point : XY) {
    point.first = std::round(point.first + offsetX);
    point.second = std::round(point.second + offsetY);
  }
  uint borderX = std::round(maxXY.first + offsetX + border_offset);
  uint borderY = std::round(maxXY.second + offsetY + border_offset);

  borderX += (4 - borderX % 4) % 4;
  borderXY = std::pair<uint, uint>{borderX, borderY};
}

void Converter::AddCircles(std::pair<double, double> &point) {
  for (int y = -rad; y <= rad; y++) {
    for (int x = -rad; x <= rad; x++) {
      if (x * x + y * y <= rad * rad) {
        int px = static_cast<int>(point.first) + x;
        int py = static_cast<int>(point.second) + y;
        // std::cout  << px << " : " << py;

        if (px >= 0 && py >= 0 && px < static_cast<int>(borderXY.first) &&
            py < static_cast<int>(borderXY.second)) {
          vertex_map[py][px] = 0;
        }
      }
    }
  }
}

void Converter::AddNumbers(int num, std::pair<int, int> point) {
  std::string number = std::to_string(num + 1);
  uint start_x = point.first + 2 * rad;
  uint start_y = point.second - rad;

  for (auto &digit : number) {
    std::string filename(1, digit);
    filename = "../src/digits/" + filename + ".bmp";
    BMP digit_img;
    digit_img.Read(filename);

    uint width = digit_img.info_header_.width;
    uint height = digit_img.info_header_.height;

    for (uint y = 0; y < height; ++y) {
      for (uint x = 0; x < width; ++x) {
        vertex_map[start_y + y][start_x + x] = digit_img.data_[y * width + x];
      }
    }

    start_x += width;
  }
};

std::vector<std::pair<int, int>> GetLine(std::pair<int, int> from,
                                         std::pair<int, int> to) {
  std::vector<std::pair<int, int>> linevec;
  const int deltaX = abs(to.first - from.first);
  const int deltaY = abs(to.second - from.second);
  const int signX = from.first < to.first ? 1 : -1;
  const int signY = from.second < to.second ? 1 : -1;
  int error = deltaX - deltaY;
  linevec.push_back(to);
  while (from.first != to.first || from.second != to.second) {
    linevec.push_back(from);
    int error2 = error * 2;
    if (error2 > -deltaY) {
      error -= deltaY;
      from.first += signX;
    }
    if (error2 < deltaX) {
      error += deltaX;
      from.second += signY;
    }
  }
  return linevec;
}

void Converter::DrawEdges(std::vector<std::vector<int>> edges,
                          std::vector<std::pair<double, double>> &XY) {
  for (auto edge : edges) {
    auto line = GetLine(XY[edge[0]], XY[edge[1]]);
    std::cout << line[0].first << std::endl;
    for (auto point : line) {
      vertex_map[point.second][point.first] = 0;
    }
  }
}

void Converter::ConvertToMap(std::vector<std::pair<double, double>> &XY,
                             std::vector<std::vector<int>> edges) {
  ComputeBorders(XY);
  std::vector<std::vector<uint8_t>> _vertex_map{
      borderXY.second, std::vector<uint8_t>(borderXY.first, 255)};
  vertex_map = _vertex_map;

  for (size_t i = 0; i < XY.size(); i++) {
    auto &point = XY[i];
    AddCircles(point);
    AddNumbers(i, point);
  }

  DrawEdges(edges, XY);
}

void Converter::Convert() {}