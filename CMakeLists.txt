cmake_minimum_required(VERSION 3.20)
project(macka LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(LayerShellQt REQUIRED)

add_executable(macka main.cpp)
target_link_libraries(macka PRIVATE Qt6::Widgets LayerShellQt::Interface)