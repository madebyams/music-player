#include "file_reader.hh"

#include <fstream>
#include <filesystem>

#include <dr_wav.h>
#include <spdlog/spdlog.h>

std::vector<float> file_reader::read_file(std::string& filename) {
  drwav wav;
  std::vector<float> audio_data{};
  auto bytes = this->read_bytes(filename);

  if(!drwav_init_memory(&wav, bytes.data(), bytes.size(), nullptr)) {
    spdlog::error("Error loading audio samples!");
    return audio_data;
  }

  audio_data.resize(wav.totalPCMFrameCount * wav.channels);
  drwav_read_pcm_frames_f32(&wav, wav.totalPCMFrameCount, audio_data.data());
  drwav_uninit(&wav);

  spdlog::debug("Audio samples loaded successfully!");
  
  return audio_data;
}

std::vector<char> file_reader::read_bytes(std::string& filename) {
  std::vector<char> bytes{};
  std::ifstream file_stream;
  size_t file_size {std::filesystem::file_size(filename)};
  
  spdlog::debug("Loading {} ({} bytes)", filename, file_size);
  bytes.resize(file_size);
  file_stream.open(filename, std::ifstream::binary | std::ifstream::in);

  file_stream.read(bytes.data(), file_size);
  spdlog::debug("Load finished!");
  
  file_stream.close();
  
  return bytes;
}
