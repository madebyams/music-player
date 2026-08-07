#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#include "arg_parser.hh"
#include "audio_engine.hh"
#include "file_reader.hh"

int main(int argc, char* argv[]) {
  std::string filename;
  int sample_rate;
  
  arg_parser arg_parser{};
  audio_engine audio_engine{};
  file_reader file_reader{};
  spdlog::cfg::load_env_levels();

  arg_parser.parse(argc, argv);
  
  filename = arg_parser.get_arg<std::string>("file");
  auto samples = file_reader.read_file(filename);

  
  spdlog::info("Playing {}", filename);
  sample_rate = arg_parser.get_arg<int>("--sample-rate");
  audio_engine.play(samples, sample_rate);
  
  return 0;
}
