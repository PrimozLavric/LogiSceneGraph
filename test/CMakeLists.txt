cmake_minimum_required (VERSION 3.10)

include("${PROJECT_SOURCE_DIR}/cmake_modules/AddSubdirectories.cmake")

# Adds googletest library and potentially other dependent library.
add_subdirectory(libs)
enable_testing()
set(SUBDIRS "core" "resources" "accelerators" "loaders")

add_subdirectories("${SUBDIRS}")