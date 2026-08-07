# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [Unreleased]

### Added

- `arg_parser` module for command-line argument parsing via [argparse](https://github.com/p-ranav/argparse).
- `--sample-rate` option to override the playback sample rate (defaults to 44100 Hz).
- `--channels` option to override the playback channel count (defaults to 2).
- `python_effect` module and `--pyfx` option to run decoded samples through a user-supplied Python script (via embedded CPython) before playback. The script's `process(samples)` function receives the samples as a Python list and its return value replaces them.
- GitLab CI pipeline that builds the binary and publishes it as a release asset on tagged commits.
- LICENSE (LGPL-2.1).

### Fixed

- Missing miniaudio implementation translation unit, causing undefined `ma_*` symbols at link time.
- Uninitialized `ma_device_config` in `audio_engine::play`, causing a segfault during playback.
- `arg_parser::get_arg<T>` defined in a `.cc` file instead of the header, causing undefined symbol errors when instantiated outside `arg_parser.cc`.
- `--sample-rate` missing a `.scan<'i', int>()` type converter, causing a `std::bad_any_cast` crash whenever the flag was passed explicitly.
- `python_effect` linking against a nonexistent `Python3` CMake target instead of `cpython::cpython`, causing `Python.h` not to be found at compile time.
- `python_effect::run` passing the script path (with its `.py` extension) straight to `PyImport_Import`, which always failed since Python interpreted the extension as a submodule path; also silently swallowed the resulting import error instead of reporting it.
- `PyObject_CallObject` being passed the raw `std::vector<float>` samples instead of a `PyObject*` argument tuple.
- Python function return values were discarded; `process()`'s return value is now converted back into the sample buffer used for playback.
- GitLab CI failing to install `cpython` on Linux: the recipe's default `with_tkinter=True` pulled in `tk`/`tcl`/`xorg`, and `xorg/system` requires X11 dev packages that Conan's package manager mode won't auto-install in CI. Disabled `with_tkinter` in `conanfile.txt`, since `python_effect` only needs the embeddable Python C API, not Tk.
