cmake_minimum_required(VERSION 3.15)
project(natty)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)

add_executable(natty
  ./natty.cpp
)

target_link_libraries(natty
  PRIVATE
  glfw
)

target_include_directories(natty
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
