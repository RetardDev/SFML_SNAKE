cmake_minimum_required(VERSION 3.26)
project(SFML_SNAKE)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics audio)

add_executable(SFML_SNAKE main.cpp)
target_link_libraries(SFML_SNAKE sfml-graphics sfml-audio)