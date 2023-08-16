#include <iostream>

#include "Kernel_3.h"
#include "Parameters_3.h"

void Kernel_3(
    hls::stream<layer17_t> &layer17_out,
    hls::stream<result_t> &layer27_out
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=layer17_out,layer27_out
    #pragma HLS DATAFLOW 

#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        // hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<conv2d_4_default_t, 36864>(w18, "w18.txt");
        nnet::load_weights_from_txt<conv2d_4_default_t, 64>(b18, "b18.txt");
        nnet::load_weights_from_txt<dense_default_t, 8192>(w22, "w22.txt");
        nnet::load_weights_from_txt<dense_default_t, 32>(b22, "b22.txt");
        nnet::load_weights_from_txt<dense_1_default_t, 320>(w25, "w25.txt");
        nnet::load_weights_from_txt<dense_1_default_t, 10>(b25, "b25.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    hls::stream<layer32_t> layer32_out("layer32_out");
    #pragma HLS STREAM variable=layer32_out depth=16
    nnet::zeropad2d_cl<layer17_t, layer32_t, config32>(layer17_out, layer32_out); // zp2d_conv2d_4

    hls::stream<layer18_t> layer18_out("layer18_out");
    #pragma HLS STREAM variable=layer18_out depth=4
    nnet::conv_2d_cl<layer32_t, layer18_t, config18>(layer32_out, layer18_out, w18, b18); // conv2d_4

    hls::stream<layer20_t> layer20_out("layer20_out");
    #pragma HLS STREAM variable=layer20_out depth=4
    nnet::relu<layer18_t, layer20_t, ReLU_config20>(layer18_out, layer20_out); // re_lu_4

    auto& layer21_out = layer20_out;
    hls::stream<layer22_t> layer22_out("layer22_out");
    #pragma HLS STREAM variable=layer22_out depth=1
    nnet::dense<layer20_t, layer22_t, config22>(layer21_out, layer22_out, w22, b22); // dense

    hls::stream<layer24_t> layer24_out("layer24_out");
    #pragma HLS STREAM variable=layer24_out depth=1
    nnet::relu<layer22_t, layer24_t, ReLU_config24>(layer22_out, layer24_out); // re_lu_5

    hls::stream<layer25_t> layer25_out("layer25_out");
    #pragma HLS STREAM variable=layer25_out depth=1
    nnet::dense<layer24_t, layer25_t, config25>(layer24_out, layer25_out, w25, b25); // dense_1

    nnet::softmax<layer25_t, result_t, Softmax_config27>(layer25_out, layer27_out); // softmax

}
