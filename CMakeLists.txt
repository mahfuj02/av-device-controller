cmake_minimum_required(VERSION 3.14)

project(AVDeviceController)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
    src/display.cpp
    src/controller.cpp
    src/parser.cpp
    # src/logger.cpp
    # src/alert.cpp
)

add_executable(av_controller ${SOURCES})

target_include_directories(av_controller PRIVATE include)