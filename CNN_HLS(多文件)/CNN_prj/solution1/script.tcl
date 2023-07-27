############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project CNN_prj
set_top CNN
add_files firmware/CNN.cpp -cflags "-std=c++0x"
add_files firmware/Kernel_1.cpp -cflags "-std=c++0x"
add_files firmware/Kernel_2.cpp -cflags "-std=c++0x"
add_files firmware/Kernel_3.cpp -cflags "-std=c++0x"
add_files -tb CNN_test.cpp -cflags "-std=c++0x -Wno-unknown-pragmas"
add_files -tb tb_data -cflags "-Wno-unknown-pragmas"
add_files -tb firmware/weights -cflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xcvu35p-fsvh2104-1-e}
create_clock -period 5 -name default
config_array_partition -maximum_size 4096
config_compile -name_max_length 80
config_schedule -enable_dsp_full_reg=0
set_clock_uncertainty 12.5%
#source "./CNN_prj/solution1/directives.tcl"
csim_design -clean -setup
csynth_design
cosim_design
export_design -format ip_catalog
