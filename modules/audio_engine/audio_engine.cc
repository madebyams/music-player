#define MINIAUDIO_IMPLEMENTATION

#include "audio_engine.hh"

#include <thread>

#include <miniaudio.h>
#include <spdlog/spdlog.h>

constexpr uint8_t CHANNELS{2};

void data_callback(
  ma_device* pDevice,
  void* pOutput,
  const void* pInput,
  ma_uint32 frameCount) {

  ma_audio_buffer* pBuffer = (ma_audio_buffer*)pDevice->pUserData;
  ma_data_source_read_pcm_frames(
   pBuffer,
   pOutput,
   frameCount,
   nullptr
  );

}

void audio_engine::play(player_buffer samples, int sample_rate) {
  ma_device device;
  ma_device_config device_config = ma_device_config_init(ma_device_type_playback);
  ma_audio_buffer buffer;
  ma_audio_buffer_config audio_buffer_config = ma_audio_buffer_config_init(
    ma_format_f32,
    CHANNELS,
    samples.size() / CHANNELS,
    samples.data(),
    nullptr
  );

  device_config.playback.format = ma_format_f32;
  device_config.playback.channels = CHANNELS;
  device_config.sampleRate = sample_rate;
  device_config.dataCallback = data_callback;
  device_config.pUserData = &buffer;
  
  if(ma_audio_buffer_init(&audio_buffer_config, &buffer) != MA_SUCCESS) {
    spdlog::error("Failed to load audio data into playback buffer!");
    return;
  }

  ma_device_init(nullptr, &device_config, &device);
  ma_device_start(&device);

  while(ma_device_is_started(&device)) {
    std::this_thread::sleep_for(
     std::chrono::seconds(100)
    );
    
  }
  ma_device_uninit(&device);
}
