# music-player

A minimal command-line WAV player written in C++.

## How it works

- `arg_parser` parses command-line arguments (file path, sample rate, channels) using [argparse](https://github.com/p-ranav/argparse).
- `file_reader` reads a WAV file from disk and decodes it to `f32` PCM samples using [dr_wav](https://github.com/mackron/dr_libs).
- `audio_engine` plays those samples back through the default output device using [miniaudio](https://miniaud.io/).
- `main` wires the three together: it parses arguments, reads the given file, and plays it.

## Requirements

- CMake >= 3.30
- [Conan](https://conan.io/) 2.x
- A C++17 compiler (tested with AppleClang)

## Building

Install dependencies with Conan, then configure and build with the generated preset:

```bash
conan install . --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
```

The `music_player` executable is written to `build/Release/main/music_player`.

## Usage

```bash
./build/Release/main/music_player path/to/file.wav
```

Optionally override the playback sample rate (defaults to 44100 Hz) and channel count (defaults to 2):

```bash
./build/Release/main/music_player path/to/file.wav --sample-rate 48000 --channels 1
```

Set `SPDLOG_LEVEL=debug` for verbose logging:

```bash
SPDLOG_LEVEL=debug ./build/Release/main/music_player path/to/file.wav
```

## Dependencies

Managed via Conan (see [conanfile.txt](conanfile.txt)):

- [spdlog](https://github.com/gabime/spdlog) — logging
- [dr_wav](https://github.com/mackron/dr_libs) — WAV decoding
- [miniaudio](https://miniaud.io/) — cross-platform audio playback
- [argparse](https://github.com/p-ranav/argparse) — command-line argument parsing

## Project layout

```
main/               CLI entry point
modules/
  arg_parser/        Command-line argument parsing via argparse
  audio_engine/      Playback via miniaudio
  file_reader/        WAV decoding via dr_wav
```

## Known limitations

- `--sample-rate` and `--channels` only change how the buffer is played back — they don't resample or remix the source audio, so mismatched values will play back distorted or at the wrong pitch/speed.
- Only WAV files are supported.
