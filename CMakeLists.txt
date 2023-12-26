cmake_minimum_required(VERSION 3.20)
project(cpp_daily)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")#指定源字符集UTF8


add_subdirectory(CppCoreGuidelines)
add_subdirectory(Learning)
add_subdirectory(Algorithm)