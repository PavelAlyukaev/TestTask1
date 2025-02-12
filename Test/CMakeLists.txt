cmake_minimum_required(VERSION 3.26)
project(Test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp)

# Включаем директорию с заголовочными файлами
include_directories( ${CMAKE_SOURCE_DIR}/Lib/include  ${CMAKE_SOURCE_DIR}/googletest/googletest/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Lib gtest gtest_main)