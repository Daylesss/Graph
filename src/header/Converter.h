#ifndef GRAPH_HEADER_VISUALIZER_H_
#define GRAPH_HEADER_VISUALIZER_H_

#include <vector>

#include "header/BMP.h"

class Converter {
  std::vector<std::vector<bool>> img;

 public:
  explicit Converter();
  void Convert();
};

#endif  // GRAPH_HEADER_VISUALIZER_H_