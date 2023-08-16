#include <iostream>

#include "Kernel_2.h"
#include "Parameters_2.h"

void Kernel_2(
    hls::stream<layer9_t> &layer9_out,
    hls::stream<layer17_t> &layer17_out
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=layer9_out,layer17_out
    #pragma HLS DATAFLOW 

#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        // hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<conv2d_2_default_t, 36864>(w10, "w10.txt");
        nnet::load_weights_from_txt<conv2d_2_default_t, 64>(b10, "b10.txt");
        nnet::load_weights_from_txt<conv2d_3_default_t, 36864>(w14, "w14.txt");
        nnet::load_weights_from_txt<conv2d_3_default_t, 64>(b14, "b14.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    hls::stream<layer30_t> layer30_out("layer30_out");
    #pragma HLS STREAM variable=layer30_out depth=100
    nnet::zeropad2d_cl<layer9_t, layer30_t, config30>(layer9_out, layer30_out); // zp2d_conv2d_2

    hls::stream<layer10_t> layer10_out("layer10_out");
    #pragma HLS STREAM variable=layer10_out depth=64
    nnet::conv_2d_cl<layer30_t, layer10_t, config10>(layer30_out, layer10_out, w10, b10); // conv2d_2

    hls::stream<layer12_t> layer12_out("layer12_out");
    #pragma HLS STREAM variable=layer12_out depth=64
    nnet::relu<layer10_t, layer12_t, ReLU_config12>(layer10_out, layer12_out); // re_lu_2

    hls::stream<layer13_t> layer13_out("layer13_out");
    #pragma HLS STREAM variable=layer13_out depth=16
    nnet::pooling2d_cl<layer12_t, layer13_t, config13>(layer12_out, layer13_out); // max_pooling2d_2

    hls::stream<layer31_t> layer31_out("layer31_out");
    #pragma HLS STREAM variable=layer31_out depth=36
    nnet::zeropad2d_cl<layer13_t, layer31_t, config31>(layer13_out, layer31_out); // zp2d_conv2d_3

    hls::stream<layer14_t> layer14_out("layer14_out");
    #pragma HLS STREAM variable=layer14_out depth=16
    nnet::conv_2d_cl<layer31_t, layer14_t, config14>(layer31_out, layer14_out, w14, b14); // conv2d_3

    hls::stream<layer16_t> layer16_out("layer16_out");
    #pragma HLS STREAM variable=layer16_out depth=16
    nnet::relu<layer14_t, layer16_t, ReLU_config16>(layer14_out, layer16_out); // re_lu_3

//    hls::stream<layer17_t> layer17_out("layer17_out");
    #pragma HLS STREAM variable=layer17_out depth=4
    nnet::pooling2d_cl<layer16_t, layer17_t, config17>(layer16_out, layer17_out); // max_pooling2d_3
}
