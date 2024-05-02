#ifndef GRAPH_HEADER_CONVERTER_H_
#define GRAPH_HEADER_CONVERTER_H_

#include <vector>

#include "BMP.h"

class Converter {
  std::vector<std::vector<bool>> img;
  int border_offset = 30;

  void prettify_data(std::vector<std::pair<double, double>> &XY);

 public:
  explicit Converter(std::vector<std::pair<double, double>> XY);  // std::vector<std::vector<int>>distances,
                                                                  // int side
  void Convert();
};

#endif  // GRAPH_HEADER_CONVERTER_H_