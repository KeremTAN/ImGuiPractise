cmake_minimum_required(VERSION 3.27)


file(GLOB im_sources "*.cpp")
file(GLOB im_headers "*.h")


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_library(imgui STATIC ${im_sources})

add_executable(demoExe ${im_sources}) # demoExe

target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(demoExe PUBLIC  ${CMAKE_SOURCE_DIR}) # demoExe

include_directories(/opt/homebrew/Cellar/glfw/3.4/include/)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL GLUT::GLUT)
target_link_libraries(demoExe PUBLIC imgui glfw OpenGL::GL GLUT::GLUT) # demoExe

