#include "arg_parser.hh"

#include <string>

arg_parser::arg_parser() {
  parser.add_argument("file")
    .help("The path of the file being played");
  
  parser.add_argument("-s", "--sample-rate")
    .help("The sample rate you want to playback the track with")
    .default_value(44100)
    .scan<'i', int>();
}

void arg_parser::parse(int argc, char* argv[]) {
  parser.parse_args(argc, argv);
}
