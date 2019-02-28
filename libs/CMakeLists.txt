# GLM
if (NOT TARGET glm)
	set(GLM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm")
	find_package(GLM REQUIRED)
	add_library(glm INTERFACE)
	target_include_directories(glm INTERFACE "${GLM_INCLUDE_DIRS}")
endif()

# Vulkan
if (NOT TARGET vulkan)
	find_package(Vulkan REQUIRED)
	add_library(vulkan UNKNOWN IMPORTED GLOBAL)
	set_target_properties(vulkan PROPERTIES
		IMPORTED_LOCATION "${Vulkan_LIBRARY}"
		INTERFACE_INCLUDE_DIRECTORIES "${Vulkan_INCLUDE_DIR}")
endif()

# TinyGLTF
add_subdirectory(tinygltf)