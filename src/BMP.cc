#include "header/BMP.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void BMP::Read(const std::string& filename) {
  std::ifstream image(filename, std::ios::binary);

  if (!image.is_open()) {
    throw std::runtime_error("File wasn't opened");
  }

  // Read headers
  image.read(reinterpret_cast<char*>(&file_header_), sizeof(FileHeader));
  image.read(reinterpret_cast<char*>(&info_header_), sizeof(InfoHeader));

  // Read color table
  for (RGB& color : color_table_) {
    image.read(reinterpret_cast<char*>(&color), sizeof(RGB));
  }

  // Read image data
  data_.resize(info_header_.size_image);
  image.read(reinterpret_cast<char*>(data_.data()), data_.size());

  image.close();
}

void BMP::Write(const std::string& filename) {
  std::ofstream image(filename, std::ios::binary);

  if (!image.is_open()) {
    throw std::runtime_error("File wasn't opened");
  }

  // Write headers
  image.write(reinterpret_cast<char*>(&file_header_), sizeof(FileHeader));
  image.write(reinterpret_cast<char*>(&info_header_), sizeof(InfoHeader));

  // Write color table
  for (const RGB& color : color_table_) {
    image.write(reinterpret_cast<const char*>(&color), sizeof(RGB));
  }

  // Write image data
  image.write(reinterpret_cast<char*>(data_.data()), data_.size());

  image.close();
}