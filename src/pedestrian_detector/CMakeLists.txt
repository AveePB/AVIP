# Standard informations 
cmake_minimum_required(VERSION 3.10.0)
project(pedestrian_detector VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED)

# Add all files
file(GLOB SOURCES 
    include/*.h                                                                                  
    src/*.cpp
)

add_executable(pedestrian_detector ${SOURCES})

target_include_directories(pedestrian_detector PRIVATE include)
target_link_libraries(pedestrian_detector ${OpenCV_LIBS})