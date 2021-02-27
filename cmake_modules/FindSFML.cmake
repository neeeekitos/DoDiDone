cmake_minimum_required(VERSION 3.2)
project(e-chess)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

# Set default build type explicitly to Release
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build type." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)

# Find SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED COMPONENTS audio graphics window system)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML couldn't be located!")
endif()


include_directories(${SFML_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES main.cpp)

add_executable(e-chess ${SOURCE_FILES})

target_link_libraries(e-chess ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})