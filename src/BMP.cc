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

void BMP::Interpret(const std::vector<std::vector<uint8_t>>& map) {
  // Clear data_ vector and reserve enough space
  // std::vector<uint8_t>().swap(data_);
  data_.reserve(map.size() * map[0].size());

  // Fill data_ vector with given data
  for (const auto& row : map) {
    data_.insert(data_.end(), row.begin(), row.end());
  }

  // // Check the correctness of the data
  // if (data_.size() != data_.capacity()) {
  //   throw std::invalid_argument("Not enough data to interpret");
  // }

  // Modify FileHeader
  file_header_.file_size = sizeof(FileHeader) + sizeof(InfoHeader) +
                           color_table_.size() * sizeof(RGB) + map.size();

  // Modify InfoHeader
  info_header_.height = map.size();
  info_header_.width = map[0].size();
  info_header_.size_image = data_.size();
}