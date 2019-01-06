# GLM
set(GLM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm")

find_package(GLM REQUIRED)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${GLM_INCLUDE_DIRS}")