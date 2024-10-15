cmake_minimum_required(VERSION 3.27)

project(ImGUI)

set(CMAKE_CXX_STANDARD 20)

file(GLOB sources "src/*.cpp")
file(GLOB headers "includes/*.h")

add_subdirectory(imgui)

add_executable(ImExe ${sources})

target_include_directories(ImExe PUBLIC ${headers})
target_link_libraries(ImExe PRIVATE imgui)