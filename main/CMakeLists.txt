add_executable(music_player
	main.cc
)

target_link_libraries(music_player
PUBLIC
	audio_engine
	arg_parser
	file_reader
	python_effect

	spdlog::spdlog
)
