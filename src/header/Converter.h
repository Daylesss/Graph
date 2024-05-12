#ifndef GRAPH_HEADER_CONVERTER_H_
#define GRAPH_HEADER_CONVERTER_H_

#include <vector>

#include "BMP.h"

// convert a vector of vertex coordinates
//  to bitmap image with this verteces
//  add numbers to this verteces and
//  draw edges between it
class Converter {
  // standart margin offset
  // need to coorectly draw points and edges of graph
  int border_offset = 30;
  // standart radius of the vertex points
  int rad = 4;

  // vector of points coordinates
  // it is with this vector
  // that we make the main transformations
  std::vector<std::pair<double, double>> XY;

  // vector of vectors with brightness of pixels
  // we use this vector to draw bmp image
  std::vector<std::vector<uint8_t>> vertex_map;

  // borders of the image
  std::pair<uint, uint> borderXY;

  // edges we have to drawn
  std::vector<std::vector<int>> edges;

  // round coordinates and make them positive
  // return the weight and height(max coordinates + offset)
  // of the image
  void ComputeBorders();
  // add circle with radius [thiss->rad]
  // to the vertex_map
  void AddCircle(std::pair<double, double> &point);
  // add number near the point
  // func use the digits from src/digits/ folder
  void AddNumber(int num, std::pair<int, int> point);

 public:
  // initialize vertex_map with computed borders
  explicit Converter(std::vector<std::vector<int>> edges,
                     std::vector<std::pair<double, double>> _XY);
  // add numbers and point circles to the vertex map
  void FillTheMap();
  // add edges between point
  // use brezenhem algorythm to drawing lines
  void DrawEdges();
  // convert vertex_map to the vector and save it as bmp
  void SaveTo(const std::string &filename);
  // high level function to do convert
  // vector of ccordinates to bmp image
  void Convert(const std::string &filename);
};

#endif  // GRAPH_HEADER_CONVERTER_H_