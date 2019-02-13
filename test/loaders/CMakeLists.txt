cmake_minimum_required(VERSION 3.2)

include("${PROJECT_SOURCE_DIR}/cmake_modules/CreateTest.cmake")

set(TEST_NAME "test_gltf_loader")
set(INCLUDES "")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(DEPENDENCIES "logi_scene_graph" "glm")

create_test("${TEST_NAME}" "${SOURCES}" "${INCLUDES}" "${DEPENDENCIES}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/testdata" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")