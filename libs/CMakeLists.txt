# GLM
if (NOT TARGET GLM::glm)
	if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glm")
		set(GLM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm")
	endif()

	find_package(GLM REQUIRED)
endif()

# Vulkan
if (NOT TARGET vulkan)
	find_package(Vulkan REQUIRED)
	add_library(vulkan ALIAS Vulkan::Vulkan)
endif()

# TinyGLTF
if (NOT TARGET tinygltf)
	add_subdirectory(tinygltf)
else()
	message(STATUS "[LogiSceneGraph] Target tinygltf is already defined. Using existing target.")
endif()