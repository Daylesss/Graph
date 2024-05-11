#ifndef GRAPH_HEADER_CONVERTER_H_
#define GRAPH_HEADER_CONVERTER_H_

#include <vector>

#include "BMP.h"

class Converter {
  int border_offset = 30;
  int rad = 4;

  std::vector<std::pair<double, double>> XY;

  std::vector<std::vector<uint8_t>> vertex_map;

  std::pair<uint, uint> borderXY;

  std::vector<std::vector<int>> edges;

  void ComputeBorders();
  void AddCircles(std::pair<double, double> &point);

  void AddNumbers(int num, std::pair<int, int> point);

 public:
  explicit Converter(std::vector<std::vector<int>> edges,
                     std::vector<std::pair<double, double>> _XY
                     // const std::string &filename
  );
  void FillTheMap();
  void DrawEdges();
  void SaveTo(const std::string &filename);
  void Convert(const std::string &filename);
};

#endif  // GRAPH_HEADER_CONVERTER_H_