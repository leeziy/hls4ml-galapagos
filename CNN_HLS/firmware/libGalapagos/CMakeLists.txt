
cmake_minimum_required(VERSION 3.3)
project(libGalapagos)

set(GALAPAGOS_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(GALAPAGOS_HLS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/xil_include")
set(DEBUG_FLAGS "-DLOG_LEVEL=2")
set(PRODUCTION_FLAGS "-O3 -DLOG_LEVEL=0")
set(CMAKE_CXX_STANDARD 14)
add_definitions(-DCPU)

include_directories(
    ${GALAPAGOS_HLS_PATH}
    "thirdparty/Catch2/single_include/catch2"
    "thirdparty/spdlog/include"
)
file(GLOB UNIT_TESTS_SOURCES unit_tests/*.cpp)

add_executable(test.exe test.cpp common.cpp ${UNIT_TESTS_SOURCES})

target_compile_options(test.exe PRIVATE
    ${DEBUG_FLAGS}
)

target_link_libraries(test.exe
    boost_thread
    boost_system
    pthread
)