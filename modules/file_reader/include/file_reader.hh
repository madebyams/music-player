#pragma once

#include <cstdint>
#include <string>
#include <vector>

class file_reader {
public:
    std::vector<float> read_file(std::string& filename);
private:
    std::vector<char> read_bytes(std::string& filename);
};
