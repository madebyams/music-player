# music-player

A minimal command-line WAV player written in C++.

## How it works

- `arg_parser` parses command-line arguments (file path, sample rate, channels, Python effect script) using [argparse](https://github.com/p-ranav/argparse).
- `file_reader` reads a WAV file from disk and decodes it to `f32` PCM samples using [dr_wav](https://github.com/mackron/dr_libs).
- `python_effect` optionally hands the decoded samples to a user-supplied Python script for processing, embedding CPython directly.
- `audio_engine` plays the (possibly effected) samples back through the default output device using [miniaudio](https://miniaud.io/).
- `main` wires it all together: it parses arguments, reads the given file, runs it through a Python effect if requested, and plays it.

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

### Python effects

Run the decoded samples through a Python script before playback with `--pyfx`:

```bash
./build/Release/main/music_player path/to/file.wav --pyfx fx.py
```

The script must define a `process(samples)` function, where `samples` is a Python list of `float` PCM samples. Whatever it returns replaces the samples used for playback — if it returns anything other than a list (or raises an error), the original, unprocessed samples are played instead. See [fx.py](fx.py) for a minimal example.

## Dependencies

Managed via Conan (see [conanfile.txt](conanfile.txt)):

- [spdlog](https://github.com/gabime/spdlog) — logging
- [dr_wav](https://github.com/mackron/dr_libs) — WAV decoding
- [miniaudio](https://miniaud.io/) — cross-platform audio playback
- [argparse](https://github.com/p-ranav/argparse) — command-line argument parsing
- [cpython](https://github.com/python/cpython) — embedded Python interpreter for `--pyfx` scripts

## Project layout

```
main/               CLI entry point
modules/
  arg_parser/        Command-line argument parsing via argparse
  audio_engine/      Playback via miniaudio
  file_reader/        WAV decoding via dr_wav
  python_effect/      Runs samples through a user Python script via embedded CPython
```

## Known limitations

- `--sample-rate` and `--channels` only change how the buffer is played back — they don't resample or remix the source audio, so mismatched values will play back distorted or at the wrong pitch/speed.
- Only WAV files are supported.
- `--pyfx` converts the whole sample buffer to a Python list of boxed floats and back, which is slow and memory-heavy for long tracks.
