#pragma once

#include <vector>

#include "file_reader.hh"

class audio_engine{
public:
  void play(player_buffer samples, int sample_rate);
};
