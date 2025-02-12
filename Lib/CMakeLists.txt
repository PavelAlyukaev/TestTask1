cmake_minimum_required(VERSION 3.26)
project(Lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
        include/stdafx.h

        include/Point.h
        include/Vector.h
        include/Tmp.h
        include/Tools.h
)

set(SOURCES
        src/Point.cpp
        src/Vector.cpp
        src/Tmp.cpp
        src/Tools.cpp
)

set(SOLUTION ${SOURCES} ${HEADERS})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/stdafx.h)
