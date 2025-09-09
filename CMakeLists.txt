cmake_minimum_required(VERSION 3.16)
project(TriGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Handle MinGW/MSYS2 on Windows ---
if (WIN32 AND MSYS)
    set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
endif()

include(FetchContent)

# --- GLFW ---
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# --- GLEW (use cmake-ready repo) ---
FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glew)

# --- OpenGL ---
find_package(OpenGL REQUIRED)

# --- Source files ---
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.h
)

add_executable(TriGL ${SOURCE_FILES}
        src/GLX/lib/prefefs.h
        src/GLX/lib/Numeric.h)

# --- Link libraries ---
target_link_libraries(TriGL PRIVATE glfw libglew_static OpenGL::GL)

# --- Include directories ---
target_include_directories(TriGL PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${glew_SOURCE_DIR}/include
)
