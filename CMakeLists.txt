cmake_minimum_required(VERSION 3.19)

project(CG2026
    LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED)


add_executable(cg2026 src/main.cpp src/glad.c)
target_include_directories(cg2026 PRIVATE include)
target_link_libraries(cg2026 PRIVATE OpenGL::GL SDL3::SDL3)