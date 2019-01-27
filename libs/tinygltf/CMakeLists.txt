cmake_minimum_required (VERSION 3.6)

add_library(tinygltf INTERFACE)
target_include_directories(tinygltf INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:lib>
)