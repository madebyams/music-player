add_library(audio_engine
	audio_engine.cc
)

target_include_directories(audio_engine
PUBLIC
	"include"
)

target_link_libraries(audio_engine
PUBLIC
	miniaudio::miniaudio
	spdlog::spdlog
PRIVATE
	file_reader
)
