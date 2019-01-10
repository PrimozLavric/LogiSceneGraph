cmake_minimum_required (VERSION 3.10)

include("${PROJECT_SOURCE_DIR}/cmake_modules/AddSubdirectories.cmake")
include("${PROJECT_SOURCE_DIR}/cmake_modules/SetupGTest.cmake")

set(GTEST_DIR "C:\\gtest" CACHE PATH "Path to gtest installation.")
setup_gtest("${GTEST_DIR}")

find_package(GTest REQUIRED PATHS "${GTEST_DIR}")

enable_testing()
set(SUBDIRS "base")

add_subdirectories("${SUBDIRS}")