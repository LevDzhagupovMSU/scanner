cmake_minimum_required(VERSION 3.10)
project(media_scanner VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp
    src/scan_result.cpp
    src/thread_scan.cpp
    src/type_file.cpp
)

add_executable(media_scanner ${SOURCES})

find_package(nlohmann_json REQUIRED)

target_include_directories(media_scanner PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(media_scanner PRIVATE
    nlohmann_json::nlohmann_json
    pthread
)
