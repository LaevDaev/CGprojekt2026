cmake_minimum_required(VERSION 3.19)

project(CG2026
    LANGUAGES CXX
)

find_package(Vulkan REQUIRED)
find_package(SDL3 REQUIRED)
find_package(glm REQUIRED)

add_executable(cg2026)

target_sources(cg2026 PRIVATE 
    src/main.cpp)

target_link_libraries(cg2026 PRIVATE Vulkan::Vulkan SDL3::SDL3 glm)