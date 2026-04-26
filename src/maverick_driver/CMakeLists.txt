cmake_minimum_required(VERSION 3.10.0)
project(maverick_driver VERSION 0.1.0 LANGUAGES C CXX)

# Add all files
file(GLOB SOURCES 
    include/*.h                                                                                  
    src/*.cpp
)

add_executable(maverick_driver ${SOURCES})

target_include_directories(maverick_driver PRIVATE include)

