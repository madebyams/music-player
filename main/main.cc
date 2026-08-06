#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#include "audio_engine.hh"
#include "file_reader.hh"

int main(int argc, char* argv[]) {
  std::string filename;
  audio_engine audio_engine{};
  file_reader file_reader{};
  
  spdlog::cfg::load_env_levels();

  if(argc < 2) {
    spdlog::error("File argument is missing!");
    spdlog::error("Exiting program");
    return 1;
  }

  filename = argv[1];
  auto samples = file_reader.read_file(filename);
  
  spdlog::info("Playing {}", filename);
  audio_engine.play(samples);
  
  return 0;
}
