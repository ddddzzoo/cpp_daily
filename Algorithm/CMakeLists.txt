cmake_minimum_required(VERSION 3.20)
project(Algorithm)

set(CMAKE_CXX_STANDARD 20)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(file ${files})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file})
endforeach()