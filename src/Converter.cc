#include "header/Converter.h"

#include <cmath>
#include <limits>
#include <vector>

#include "header/BMP.h"
#include "header/Graph.h"

Converter::Converter(std::vector<std::vector<int>> _edges,
                     std::vector<std::pair<double, double>> _XY) {
  edges = _edges;
  XY = _XY;
  ComputeBorders();
  // init vertex map
  std::vector<std::vector<uint8_t>> _vertex_map{
      borderXY.second, std::vector<uint8_t>(borderXY.first, 255)};
  vertex_map = _vertex_map;
}

void Converter::SaveTo(const std::string &filename) {
  // create new BMP
  BMP graph_img;
  // make vector from the 2d matrix
  graph_img.Interpret(vertex_map);
  // write to the file
  graph_img.Write(filename);
};

void Converter::ComputeBorders() {
  // init minXY with max values to find the minimal
  std::pair<double, double> minXY{std::numeric_limits<double>::max(),
                                  std::numeric_limits<double>::max()};
  // as for minXY
  std::pair<double, double> maxXY{std::numeric_limits<double>::min(),
                                  std::numeric_limits<double>::min()};
  // find min and max values in the loop
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
  // if the min values is positive - offset is default
  // else we increase offset to make all values >> default offset
  // after summing
  double offsetX =
      minXY.first > 0 ? border_offset : border_offset - minXY.first;
  double offsetY =
      minXY.second > 0 ? border_offset : border_offset - minXY.second;
  // round coordinates
  // because positions in the vector can not be non-integer
  for (auto &point : XY) {
    // adding offset to all cordinates to make
    // minimal value >= default offset (30)
    point.first = std::round(point.first + offsetX);
    point.second = std::round(point.second + offsetY);
  }
  // borders is max values + offset
  uint borderX = std::round(maxXY.first + offsetX + border_offset);
  uint borderY = std::round(maxXY.second + offsetY + border_offset);
  // add padding to border
  // (needint the bmp to optimize memory)
  borderX += (4 - borderX % 4) % 4;
  borderXY = std::pair<uint, uint>{borderX, borderY};
}

void Converter::AddCircle(std::pair<double, double> &point) {
  for (int y = -rad; y <= rad; y++) {
    for (int x = -rad; x <= rad; x++) {
      // if pixel in the circle
      // (circle equation is x^2+y^2=r^2)
      // set it black
      if (x * x + y * y <= rad * rad) {
        int px = static_cast<int>(point.first) + x;
        int py = static_cast<int>(point.second) + y;
        // check if the pixel not in the borders
        if (px >= 0 && py >= 0 && px < static_cast<int>(borderXY.first) &&
            py < static_cast<int>(borderXY.second)) {
          // set the pixel black
          vertex_map[py][px] = 0;
        }
      }
    }
  }
}

void Converter::AddNumber(int num, std::pair<int, int> point) {
  // increase number vecouse we decreade it in the Graph constructor
  std::string number = std::to_string(num + 1);
  // set the start cordinates to draw digit
  uint start_x = point.first + 2 * rad;  // right side of the point
  uint start_y = point.second - rad;     // from the downside

  // add the digits consequently
  for (auto &digit : number) {
    std::string filename(1, digit);
    // read the digit bmp from the folder
    filename = "../src/digits/" + filename + ".bmp";
    BMP digit_img;
    digit_img.Read(filename);

    uint width = digit_img.info_header_.width;
    uint height = digit_img.info_header_.height;
    // draw digit
    for (uint y = 0; y < height; ++y) {
      for (uint x = 0; x < width; ++x) {
        vertex_map[start_y + y][start_x + x] = digit_img.data_[y * width + x];
      }
    }
    // offset start to draw another digit
    start_x += width;
  }
};

std::vector<std::pair<int, int>> GetLine(std::pair<int, int> from,
                                         std::pair<int, int> to) {
  // vector vith coordinates of all points
  // belonged to edge
  std::vector<std::pair<int, int>> linevec;
  // brezenhem algorythm
  // we compare coordinates of the point with
  // cordinate of the center of line
  // and add them to linevec
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

void Converter::DrawEdges() {
  // draw the edges int he loop
  for (auto edge : edges) {
    auto line = GetLine(XY[edge[0]], XY[edge[1]]);
    // set all the pixels in line to black color
    for (auto point : line) {
      vertex_map[point.second][point.first] = 0;
    }
  }
}

void Converter::FillTheMap() {
  // add circle and number for all vertexes int the loop
  for (size_t i = 0; i < XY.size(); i++) {
    auto &point = XY[i];
    AddCircle(point);
    AddNumber(i, point);
  }
}

void Converter::Convert(const std::string &filename) {
  // aggragate all functions in the one
  FillTheMap();
  DrawEdges();
  SaveTo(filename);
}