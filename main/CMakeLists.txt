add_executable(music_player
	main.cc
)

target_link_libraries(music_player
PUBLIC
	audio_engine
	file_reader

	spdlog::spdlog
)
