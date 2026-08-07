#pragma once

#include <cstdint>
#include <string>
#include <vector>

using player_buffer = std::vector<float>;

class file_reader {
public:
  player_buffer read_file(std::string& filename);
  std::string read_text_file(std::string& filename);
private:
    std::vector<char> read_bytes(std::string& filename);
};
