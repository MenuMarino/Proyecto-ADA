cmake_minimum_required(VERSION 3.14.5)
project(Proyecto)

set(CMAKE_CXX_STANDARD 14)
set(SRC_FILES main.cpp MinMatch.h MatrixTransformer.h)

include_directories(.)

find_package(OpenCV REQUIRED)
add_executable(
        ${PROJECT_NAME}
        ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
