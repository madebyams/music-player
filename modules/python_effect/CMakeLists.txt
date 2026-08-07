add_library(python_effect
	python_effect.cc
)

target_include_directories(python_effect
PUBLIC
	"include"
)

target_link_libraries(python_effect
PUBLIC
	file_reader
	cpython::cpython
)
