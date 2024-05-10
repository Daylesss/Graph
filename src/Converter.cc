#include "header/Converter.h"

#include <cmath>
#include <limits>
#include <vector>

#include "header/BMP.h"
#include "header/Graph.h"

Converter::Converter(
    // std::vector<std::vector<int>>distances,
    std::vector<std::pair<double, double>> XY, const std::string &filename
    //  int side
) {
  auto &points = XY;
  auto vertex_map = prettify_data(points);

  BMP graph_img;
  graph_img.Interpret(vertex_map);
  graph_img.Write(filename);
  //   std::vector<std::vector<>>
}

std::pair<uint, uint> Converter::GetBorders(
    std::vector<std::pair<double, double>> &XY) {
  std::pair<int, int> minXY{std::numeric_limits<double>::max(),
                            std::numeric_limits<double>::max()};
  std::pair<int, int> maxXY{std::numeric_limits<double>::min(),
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
    if (point.second < minXY.second) {
      minXY.second = point.second;
    }
  }
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
  return std::pair<uint, uint>{borderX, borderY};
}

void Converter::AddCircles(std::pair<double, double> &point,
                           std::pair<uint, uint> borderXY,
                           std::vector<std::vector<uint8_t>> &vertex_map) {
  for (int y = -rad; y <= rad; y++) {
    for (int x = -rad; x <= rad; x++) {
      if (x * x + y * y <= rad * rad) {
        int px = static_cast<int>(point.first) + x;
        int py = static_cast<int>(point.second) + y;

        if (px >= 0 && py >= 0 && px < borderXY.first && py < borderXY.second) {
          vertex_map[py][px] = 0;
        }
      }
    }
  }
}

void Converter::AddNumbers(int num, std::pair<int, int> point,
                           std::vector<std::vector<uint8_t>> vertex_map) {
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

std::vector<std::vector<uint8_t>> Converter::prettify_data(
    std::vector<std::pair<double, double>> &XY) {
  std::pair<uint, uint> borderXY = GetBorders(XY);
  std::vector<std::vector<uint8_t>> vertex_map{
      borderXY.second, std::vector<uint8_t>(borderXY.first, 255)};

  for (int i = 0; i < XY.size(); i++) {
    auto &point = XY[i];
    AddCircles(point, borderXY, vertex_map);
    AddNumbers(i, point, vertex_map);
  }
  return vertex_map;
}

void Converter::Convert() {}