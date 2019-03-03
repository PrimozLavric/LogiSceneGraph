cmake_minimum_required (VERSION 3.6)

if (NOT TARGET tinygltf)
	add_library(tinygltf "${CMAKE_CURRENT_SOURCE_DIR}/src.cpp")
	target_include_directories(tinygltf PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
			$<INSTALL_INTERFACE:lib>
	)
endif()