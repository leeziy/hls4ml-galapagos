#include <iostream>

#include "CNN.h"
//#include "parameters.h"

#include "Kernel_1.h"
#include "Kernel_2.h"
#include "Kernel_3.h"

void CNN(
    hls::stream<input_t> &input_1,
    hls::stream<result_t> &layer23_out
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=input_1,layer23_out 
    #pragma HLS DATAFLOW 

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

	hls::stream<layer9_t> layer9_out("layer9_out");
	Kernel_1(input_1,layer9_out);

	hls::stream<layer16_t> layer16_out("layer16_out");
	Kernel_2(layer9_out,layer16_out);

	Kernel_3(layer16_out,layer23_out);
}

