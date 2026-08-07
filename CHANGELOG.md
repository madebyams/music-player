# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [Unreleased]

### Added

- `arg_parser` module for command-line argument parsing via [argparse](https://github.com/p-ranav/argparse).
- `--sample-rate` option to override the playback sample rate (defaults to 44100 Hz).
- `--channels` option to override the playback channel count (defaults to 2).
- GitLab CI pipeline that builds the binary and publishes it as a release asset on tagged commits.
- LICENSE (LGPL-2.1).

### Fixed

- Missing miniaudio implementation translation unit, causing undefined `ma_*` symbols at link time.
- Uninitialized `ma_device_config` in `audio_engine::play`, causing a segfault during playback.
- `arg_parser::get_arg<T>` defined in a `.cc` file instead of the header, causing undefined symbol errors when instantiated outside `arg_parser.cc`.
- `--sample-rate` missing a `.scan<'i', int>()` type converter, causing a `std::bad_any_cast` crash whenever the flag was passed explicitly.
