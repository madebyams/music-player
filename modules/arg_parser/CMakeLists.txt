add_library(arg_parser
	arg_parser.cc
)

target_include_directories(arg_parser
PUBLIC
	"include"
)

target_link_libraries(arg_parser
PUBLIC
	argparse::argparse
)
