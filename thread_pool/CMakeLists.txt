cmake_minimum_required(VERSION 3.9)

# list the header files
set(HEADER_FILES
	include/pool/Queue.h
	include/pool/Thread_Pool.h
)

# add library target
add_library(pool INTERFACE)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TOOL_FILES})


# Windows specfic flags to enable W variations of winapi
if(WIN32)
	target_compile_definitions(pool
		INTERFACE
			OS_WINDOWS=1
	)
endif()


# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(pool INTERFACE cxx_std_17)

# define debug macro
target_compile_definitions(pool INTERFACE "$<$<CONFIG:DEBUG>:DEBUG>")

# list include directories
target_include_directories(pool
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
