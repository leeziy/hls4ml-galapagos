#include <iostream>

#include "Kernel_3.h"
#include "Parameters_3.h"

void Kernel_3(
    hls::stream<layer16_t> &layer16_out,
    hls::stream<result_t> &layer23_out
){
    // hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=layer16_out,layer23_out
    #pragma HLS DATAFLOW

#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        // hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<dense_default_t, 131072>(w18, "w18.txt");
        nnet::load_weights_from_txt<dense_default_t, 128>(b18, "b18.txt");
        nnet::load_weights_from_txt<dense_1_default_t, 1280>(w21, "w21.txt");
        nnet::load_weights_from_txt<dense_1_default_t, 10>(b21, "b21.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    auto& layer17_out = layer16_out;
    hls::stream<layer18_t> layer18_out("layer18_out");
    #pragma HLS STREAM variable=layer18_out depth=1
    nnet::dense<layer16_t, layer18_t, config18>(layer17_out, layer18_out, w18, b18); // dense

    hls::stream<layer20_t> layer20_out("layer20_out");
    #pragma HLS STREAM variable=layer20_out depth=1
    nnet::relu<layer18_t, layer20_t, ReLU_config20>(layer18_out, layer20_out); // re_lu_4

    hls::stream<layer21_t> layer21_out("layer21_out");
    #pragma HLS STREAM variable=layer21_out depth=1
    nnet::dense<layer20_t, layer21_t, config21>(layer20_out, layer21_out, w21, b21); // dense_1

    nnet::softmax<layer21_t, result_t, Softmax_config23>(layer21_out, layer23_out); // softmax
}
