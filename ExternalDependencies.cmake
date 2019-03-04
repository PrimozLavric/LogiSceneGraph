# GLM
if (NOT TARGET GLM::glm)
	if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm")
		set(GLM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm")
	endif()

	find_package(GLM REQUIRED)
else()
	message(STATUS "[LogiSceneGraph] Target GLM::glm is already defined. Using existing target.")
endif()

# Vulkan
if (NOT TARGET Vulkan::Vulkan)
	find_package(Vulkan REQUIRED)
else()
	message(STATUS "[LogiSceneGraph] Target Vulkan::Vulkan is already defined. Using existing target.")
endif()

# TinyGLTF
if (NOT TARGET tinygltf)
	add_subdirectory(libs/tinygltf)
else()
	message(STATUS "[LogiSceneGraph] Target tinygltf is already defined. Using existing target.")
endif()