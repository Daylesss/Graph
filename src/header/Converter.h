#ifndef GRAPH_HEADER_CONVERTER_H_
#define GRAPH_HEADER_CONVERTER_H_

#include <vector>

#include "BMP.h"

class Converter {
  std::vector<std::vector<bool>> img;
  int border_offset = 30;
  int rad = 4;

  std::pair<uint, uint> GetBorders(std::vector<std::pair<double, double>> &XY);
  void AddCircles(std::pair<double, double> &point,
                  std::pair<uint, uint> borderXY,
                  std::vector<std::vector<uint8_t>> &vertex_map);

  void AddNumbers(int num, std::pair<int, int> point,
                  std::vector<std::vector<uint8_t>> &vertex_map);
  std::vector<std::vector<uint8_t>> prettify_data(
      std::vector<std::pair<double, double>> &XY);

 public:
  explicit Converter(
      std::vector<std::pair<double, double>> XY,
      const std::string &filename);  // std::vector<std::vector<int>>distances,
                                     // int side
  void Convert();
};

#endif  // GRAPH_HEADER_CONVERTER_H_