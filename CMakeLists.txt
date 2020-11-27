cmake_minimum_required(VERSION 3.10)

project(bf)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

add_compile_options(-Wall -Wextra -Werror)

add_executable(pb src/main.cpp src/pb.cpp)
