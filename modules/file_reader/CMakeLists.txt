add_library(file_reader
	file_reader.cc
)

target_include_directories(file_reader
PUBLIC
	"include"
)

target_link_libraries(file_reader
PUBLIC
	spdlog::spdlog
	drwav::drwav
)
