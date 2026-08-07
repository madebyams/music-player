#pragma once

#include <string>

#include "file_reader.hh"

class python_effect {
public:
  player_buffer run(std::string script_path, player_buffer samples);
};
