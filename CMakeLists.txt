cmake_minimum_required(VERSION 3.9)

project(Thread-Pool VERSION 1.0.0 LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")

# internal libraries
add_subdirectory(thread_pool)
add_subdirectory(playground)

# Organize Targets into folders

set_target_properties(
	playground
	PROPERTIES FOLDER Testing
)