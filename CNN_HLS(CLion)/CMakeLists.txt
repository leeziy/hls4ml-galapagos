cmake_minimum_required(VERSION 3.26)
project(CNN_HLS)

set(CMAKE_CXX_STANDARD 20)

add_executable(CNN_HLS
        Galapagos_CNN_test.cpp
        firmware/Kernel_1.cpp
        firmware/Kernel_2.cpp
        firmware/Kernel_3.cpp
        firmware/Galapagos_Kernel_1.cpp
        firmware/Galapagos_Kernel_2.cpp
        firmware/Galapagos_Kernel_3.cpp)

include_directories(/home/leeziy/software/Xilinx/Vivado/2019.2/include)
include_directories(/home/leeziy/software/Xilinx/Vivado/2019.2/lnx64)