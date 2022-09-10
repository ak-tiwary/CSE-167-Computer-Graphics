# This CMakeLists is intended only for macOS and Linux.

cmake_minimum_required(VERSION 3.1)

# Set a project name.
project(HelloOpenGL)

# Use the C++17 standard.
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_FIND_DEBUG_MODE 0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Suppress warnings of the deprecation of glut functions on macOS.
add_definitions(-Wno-deprecated-declarations)




# Find the packages we need.
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


find_package(OpenCV 4 REQUIRED)







# OPENGL_INCLUDE_DIR, GLUT_INCLUDE_DIR, OPENGL_LIBRARIES, and GLUT_LIBRARIES
# are CMake built-in variables defined when the packages are found.

set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
set(LIBRARIES ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})


include_directories(${INCLUDE_DIRS})
include_directories(/usr/local/include)


# Add the list of include paths to be used to search for include files.


add_subdirectory(${PROJECT_SOURCE_DIR}/src)