cmake_minimum_required(VERSION 3.10)
project("DialogShitProject")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_USE_UNICODE_CHARACTERS OFF)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")

# Include directories
include_directories("${PROJECT_SOURCE_DIR}/include")


# Add subdirectory for src with specified binary directory
add_subdirectory(src "${PROJECT_SOURCE_DIR}/src")
