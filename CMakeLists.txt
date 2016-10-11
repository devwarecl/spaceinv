
cmake_minimum_required(VERSION 3.2)

project(spaceinv)

find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)
find_package(Boost 
    COMPONENTS 
        filesystem
        system 
        unit_test_framework 
        timer 
        log 
        thread 

    REQUIRED
)

set(CMAKE_CXX_STANDARD 14)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_definitions (-DBOOST_ALL_DYN_LINK)
add_definitions (-DBOOST_ALL_NO_LIB)
add_definitions (-DBOOST_TEST_DYN_LINK)

include_directories(${glfw3_DIR}/include)
include_directories(${glbinding_DIR}/include)
include_directories(${FREEIMAGE_INCLUDE_DIR})
include_directories(${LIBBDM_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${OPENAL_INCLUDE_DIR})
include_directories(src)

link_directories(${glbinding_DIR}/lib)
link_directories(${FREEIMAGE_LIBRARY_DIR})
link_directories(${LIBBDM_LIBRARY_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(src/spaceinv)
add_subdirectory(src/xe)
