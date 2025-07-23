# Find all .cpp files in src directory
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Find all .h files in include directory
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/../include/*.h")

# Create the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories for the target
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/../include")

set(CMAKE_USE_UNICODE_CHARACTERS OFF)

