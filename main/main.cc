#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#include "arg_parser.hh"
#include "audio_engine.hh"
#include "file_reader.hh"
#include "python_effect.hh"

int main(int argc, char* argv[]) {
  std::string filename;
  std::string python_effect_filename;
  int sample_rate;
  int channels;
  
  arg_parser arg_parser{};
  audio_engine audio_engine{};
  file_reader file_reader{};
  python_effect python_effect{};
  spdlog::cfg::load_env_levels();

  arg_parser.parse(argc, argv);
  
  filename = arg_parser.get_arg<std::string>("file");
  auto samples = file_reader.read_file(filename);

  python_effect_filename = arg_parser.get_arg<std::string>("--pyfx");
  spdlog::debug("Running PyFx {}", python_effect_filename);
  samples = python_effect.run(python_effect_filename, samples);
  
  spdlog::info("Playing {}", filename);
  sample_rate = arg_parser.get_arg<int>("--sample-rate");
  channels = arg_parser.get_arg<int>("--channels");
  audio_engine.play(samples, sample_rate, channels);
  
  return 0;
}
