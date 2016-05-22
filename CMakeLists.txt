
cmake_minimum_required(VERSION 3.2)

project(spaceinv)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)

set (CMAKE_CXX_STANDARD 14)

include_directories(${glfw3_DIR}/include)
include_directories(${glbinding_DIR}/include)
include_directories(${FREEIMAGE_INCLUDE_DIR})
include_directories(${LIBBDM_INCLUDE_DIR})
include_directories(src)

link_directories(${glbinding_DIR}/lib)
link_directories(${FREEIMAGE_LIBRARY_DIR})
link_directories(${LIBBDM_LIBRARY_DIR})

add_subdirectory(src/spaceinv)
add_subdirectory(src/xe)
