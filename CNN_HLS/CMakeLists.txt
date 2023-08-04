cmake_minimum_required(VERSION 3.3)
project(CNN_HLS)

# search path
set(CMAKE_CXX_STANDARD 14)
set(GALAPAGOS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/firmware/libGalapagos")
set(GALAPAGOS_HLS_PATH "${GALAPAGOS_PATH}/xil_include")
# message("GALAPAGOS_PATH: ${CMAKE_CURRENT_SOURCE_DIR}/firmware/libGalapagos")

#compiler parameters
add_definitions(-DCPU)
set(DEBUG_FLAGS "-DLOG_LEVEL=2")
set(PRODUCTION_FLAGS "-O3 -DLOG_LEVEL=0")


include_directories(${GALAPAGOS_PATH})
include_directories(${GALAPAGOS_HLS_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/firmware/ap_types)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/firmware/nnet_utils)


add_executable(CNN_HLS CNN_test.cpp firmware/CNN.cpp)


target_link_libraries(CNN_HLS
    boost_thread
    boost_system
    pthread
)