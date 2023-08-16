#include <iostream>

#include "Kernel_1.h"
#include "Parameters_1.h"

void Kernel_1(
    hls::stream<input_t> &input_1,
    hls::stream<layer9_t> &layer9_out
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=input_1,layer9_out
    #pragma HLS DATAFLOW 

#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        // hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<conv2d_default_t, 1728>(w2, "w2.txt");
        nnet::load_weights_from_txt<conv2d_default_t, 64>(b2, "b2.txt");
        nnet::load_weights_from_txt<conv2d_1_default_t, 36864>(w6, "w6.txt");
        nnet::load_weights_from_txt<conv2d_1_default_t, 64>(b6, "b6.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    hls::stream<layer28_t> layer28_out("layer28_out");
    #pragma HLS STREAM variable=layer28_out depth=1156
    nnet::zeropad2d_cl<input_t, layer28_t, config28>(input_1, layer28_out); // zp2d_conv2d

    hls::stream<layer2_t> layer2_out("layer2_out");
    #pragma HLS STREAM variable=layer2_out depth=1024
    nnet::conv_2d_cl<layer28_t, layer2_t, config2>(layer28_out, layer2_out, w2, b2); // conv2d

    hls::stream<layer4_t> layer4_out("layer4_out");
    #pragma HLS STREAM variable=layer4_out depth=1024
    nnet::relu<layer2_t, layer4_t, ReLU_config4>(layer2_out, layer4_out); // re_lu

    hls::stream<layer5_t> layer5_out("layer5_out");
    #pragma HLS STREAM variable=layer5_out depth=256
    nnet::pooling2d_cl<layer4_t, layer5_t, config5>(layer4_out, layer5_out); // max_pooling2d

    hls::stream<layer29_t> layer29_out("layer29_out");
    #pragma HLS STREAM variable=layer29_out depth=324
    nnet::zeropad2d_cl<layer5_t, layer29_t, config29>(layer5_out, layer29_out); // zp2d_conv2d_1

    hls::stream<layer6_t> layer6_out("layer6_out");
    #pragma HLS STREAM variable=layer6_out depth=256
    nnet::conv_2d_cl<layer29_t, layer6_t, config6>(layer29_out, layer6_out, w6, b6); // conv2d_1

    hls::stream<layer8_t> layer8_out("layer8_out");
    #pragma HLS STREAM variable=layer8_out depth=256
    nnet::relu<layer6_t, layer8_t, ReLU_config8>(layer6_out, layer8_out); // re_lu_1

//    hls::stream<layer9_t> layer9_out("layer9_out");
    #pragma HLS STREAM variable=layer9_out depth=64
    nnet::pooling2d_cl<layer8_t, layer9_t, config9>(layer8_out, layer9_out); // max_pooling2d_1
}
