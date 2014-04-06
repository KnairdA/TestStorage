cmake_minimum_required(VERSION 2.8)
project(TestStorage)

set(
	CMAKE_CXX_FLAGS
	"-std=c++11 -W -Wall -Wextra -Winline -pedantic"
)

include_directories(
	lib/BinaryMapping/src/
	lib/
	src/
)

add_executable(
	test
	test.cc
	src/io/buffer_guard.cc
	src/io/file.cc
)
