cmake_minimum_required(VERSION 2.8)

project(genclass)

SET(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")
SET(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(
	include/
)

file(
	GLOB_RECURSE
	source_files
	src/*
)

file(
	GLOB_RECURSE
	header_files
	include/*
)

add_executable(
	genclass
	${header_files}
	${source_files}
)

