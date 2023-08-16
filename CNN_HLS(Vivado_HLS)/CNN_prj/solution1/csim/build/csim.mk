# ==============================================================
# Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
# Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
# ==============================================================
CSIM_DESIGN = 1

__SIM_FPO__ = 1

__HLS_FPO_v6_1__ = 1

__SIM_MATHHLS__ = 1

__SIM_OPENCV__ = 1

__SIM_FFT__ = 1

__SIM_FIR__ = 1

__SIM_DDS__ = 1

ObjDir = obj

HLS_SOURCES = ../../../../Galapagos_CNN_test.cpp ../../../../firmware/Galapagos_Kernel_1.cpp ../../../../firmware/Galapagos_Kernel_2.cpp ../../../../firmware/Galapagos_Kernel_3.cpp ../../../../firmware/Kernel_1.cpp ../../../../firmware/Kernel_2.cpp ../../../../firmware/Kernel_3.cpp

TARGET := csim.exe

AUTOPILOT_ROOT := /home/leeziy/software/Xilinx/Vivado/2019.2
AUTOPILOT_MACH := lnx64
ifdef AP_GCC_M32
  AUTOPILOT_MACH := Linux_x86
  IFLAG += -m32
endif
IFLAG += -fPIC
ifndef AP_GCC_PATH
  AP_GCC_PATH := /home/leeziy/software/Xilinx/Vivado/2019.2/tps/lnx64/gcc-6.2.0/bin
endif
AUTOPILOT_TOOL := ${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools
AP_CLANG_PATH := ${AUTOPILOT_TOOL}/clang-3.9/bin
AUTOPILOT_TECH := ${AUTOPILOT_ROOT}/common/technology


IFLAG += -I "${AUTOPILOT_TOOL}/systemc/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include/opencv"
IFLAG += -I "${AUTOPILOT_ROOT}/include/ap_sysc"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_FP_comp"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_comp"
IFLAG += -I "${AUTOPILOT_TOOL}/auto_cc/include"
IFLAG += -I "/usr/include/x86_64-linux-gnu"
IFLAG += -D__SIM_FPO__

IFLAG += -D__HLS_FPO_v6_1__

IFLAG += -D__SIM_OPENCV__

IFLAG += -D__SIM_FFT__

IFLAG += -D__SIM_FIR__

IFLAG += -D__SIM_DDS__

IFLAG += -D__DSP48E2__
IFLAG += -std=c++0x -Wno-unknown-pragmas 
IFLAG += -g
DFLAG += -D__xilinx_ip_top= -DAESL_TB
CCFLAG += 
TOOLCHAIN += 



include ./Makefile.rules

all: $(TARGET)



$(ObjDir)/Galapagos_CNN_test.o: ../../../../Galapagos_CNN_test.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../Galapagos_CNN_test.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -std=c++0x -Wno-unknown-pragmas  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/Galapagos_CNN_test.d

$(ObjDir)/Galapagos_Kernel_1.o: ../../../../firmware/Galapagos_Kernel_1.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../firmware/Galapagos_Kernel_1.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -std=c++0x  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/Galapagos_Kernel_1.d

$(ObjDir)/Galapagos_Kernel_2.o: ../../../../firmware/Galapagos_Kernel_2.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../firmware/Galapagos_Kernel_2.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -std=c++0x  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/Galapagos_Kernel_2.d

$(ObjDir)/Galapagos_Kernel_3.o: ../../../../firmware/Galapagos_Kernel_3.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../firmware/Galapagos_Kernel_3.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -std=c++0x  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/Galapagos_Kernel_3.d

$(ObjDir)/Kernel_1.o: ../../../../firmware/Kernel_1.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../firmware/Kernel_1.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -std=c++0x  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/Kernel_1.d

$(ObjDir)/Kernel_2.o: ../../../../firmware/Kernel_2.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../firmware/Kernel_2.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -std=c++0x  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/Kernel_2.d

$(ObjDir)/Kernel_3.o: ../../../../firmware/Kernel_3.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../firmware/Kernel_3.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -std=c++0x  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/Kernel_3.d
