cmake_minimum_required(VERSION 3.10)
project(task1 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp
    src/scan_result.cpp
    src/thread_scan.cpp
    src/type_file.cpp
)

add_executable(task1 ${SOURCES})

find_package(nlohmann_json REQUIRED)

target_include_directories(task1 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(task1 PRIVATE
    nlohmann_json::nlohmann_json
    pthread
)
