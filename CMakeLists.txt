cmake_minimum_required(VERSION 3.30)
project(music_player CXX)

find_package(spdlog REQUIRED)
find_package(drwav REQUIRED)
find_package(miniaudio REQUIRED)

add_subdirectory(main)
add_subdirectory(modules)
