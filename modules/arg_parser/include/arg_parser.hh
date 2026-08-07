#pragma once

#include <argparse/argparse.hpp>

class arg_parser {
public:
  arg_parser();
  void parse(int argc, char* argv[]);

  template <typename T>
  inline T get_arg(std::string name) {
    return parser.get<T>(name);
  }
private:
  argparse::ArgumentParser parser{"music_player"};
};
