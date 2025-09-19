cmake_minimum_required(VERSION 3.16)
project(TriGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# --- GLEW (Perlmint cmake fork) ---
FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glew)

# --- GLM (Header-only) ---
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glm)

# --- OpenGL ---
find_package(OpenGL REQUIRED)

# --- Sources ---
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.h
)

add_executable(TriGL
        ${SOURCE_FILES}
        src/util/Transformer.h
)

# --- Link everything ---
target_link_libraries(TriGL PRIVATE
        glfw
        libglew_static   # provided by glew-cmake
        OpenGL::GL
        glm              # glm target comes from FetchContent
)

# No need to add glew include manually — target brings them
target_include_directories(TriGL PRIVATE
        ${OPENGL_INCLUDE_DIR}  # optional, sometimes not needed
)
