# //////////////////////////////////////////////////////////////////////////////////////
# /////////////////////////////////////  STANDARDS  ////////////////////////////////////
# //////////////////////////////////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.0)

# //////////////////////////////////////////////////////////////////////////////////////
# ///////////////////////////////  CONFIGURATION PROJECT  //////////////////////////////
# //////////////////////////////////////////////////////////////////////////////////////

project(WorldIMaker)

set(EXECUTABLE_NAME WorldIMaker)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -lSDL2 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## ------------------------------ For UPEM compilation ------------------------------ ##

if(UPEMLV)
    set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)
endif(UPEMLV)

## ---------------------------------------------------------------------------------- ##

# //////////////////////////////////////////////////////////////////////////////////////
# ////////////////////////////////////  DEPENDENCIES  //////////////////////////////////
# //////////////////////////////////////////////////////////////////////////////////////

# OpenGL
find_package(OpenGL REQUIRED)
if(${OpenGL_FOUND})
    message(STATUS "OpenGL found")
endif()

# GLEW
find_package(GLEW REQUIRED)
if(${GLEW_FOUND})
    message(STATUS "GLEW found")
endif()

# SDL2
# On windows
if (WIN32) 
    set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/include)
    set(SDL2_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/lib/x64/SDL2.lib;
                       ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/lib/x64/SDL2main.lib)
# On linux
else()
find_package(SDL2 REQUIRED)
if(${SDL2_FOUND})
    message(STATUS "SDL2 found")
endif()
endif()

# Eigen
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "EIGEN3 found")
else()
    include_directories("/usr/include/eigen3") # manually specify the include location
endif()

# //////////////////////////////////////////////////////////////////////////////////////
# //////////////////////////////////////  INCLUDES  ////////////////////////////////////
# //////////////////////////////////////////////////////////////////////////////////////

include_directories(
		${SDL2_INCLUDE_DIRS}
		${OPENGL_INCLUDE_DIR}
		${GLEW_INCLUDE_DIR}
		${EIGEN3_INCLUDE_DIRS}
		lib/glimac/include
		lib/glm/include
		lib/imgui/include)

set(ALL_LIBRARIES glimac imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(lib/glimac)
add_subdirectory(lib/imgui)

# //////////////////////////////////////////////////////////////////////////////////////
# ////////////////////////////////////  PROJECT FILES  /////////////////////////////////
# //////////////////////////////////////////////////////////////////////////////////////

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)
file(GLOB_RECURSE SHADER_FILES shaders/*.glsl)

# //////////////////////////////////////////////////////////////////////////////////////
# //////////////////////////////////////  EXECUTABLE  //////////////////////////////////
# //////////////////////////////////////////////////////////////////////////////////////

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})

target_link_libraries(${EXECUTABLE_NAME} ${ALL_LIBRARIES})

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})