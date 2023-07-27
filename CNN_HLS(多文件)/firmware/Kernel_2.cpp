#include <iostream>

#include "Kernel_2.h"
#include "Parameters_2.h"

void Kernel_2(
    hls::stream<layer9_t> &layer9_out,
    hls::stream<layer16_t> &layer16_out
){
    // hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=layer9_out,layer16_out
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

    hls::stream<layer26_t> layer26_out("layer26_out");
    #pragma HLS STREAM variable=layer26_out depth=100
    nnet::zeropad2d_cl<layer9_t, layer26_t, config26>(layer9_out, layer26_out); // zp2d_conv2d_2

    hls::stream<layer10_t> layer10_out("layer10_out");
    #pragma HLS STREAM variable=layer10_out depth=64
    nnet::conv_2d_cl<layer26_t, layer10_t, config10>(layer26_out, layer10_out, w10, b10); // conv2d_2

    hls::stream<layer12_t> layer12_out("layer12_out");
    #pragma HLS STREAM variable=layer12_out depth=64
    nnet::relu<layer10_t, layer12_t, ReLU_config12>(layer10_out, layer12_out); // re_lu_2

    hls::stream<layer13_t> layer13_out("layer13_out");
    #pragma HLS STREAM variable=layer13_out depth=16
    nnet::pooling2d_cl<layer12_t, layer13_t, config13>(layer12_out, layer13_out); // max_pooling2d_2

    hls::stream<layer27_t> layer27_out("layer27_out");
    #pragma HLS STREAM variable=layer27_out depth=36
    nnet::zeropad2d_cl<layer13_t, layer27_t, config27>(layer13_out, layer27_out); // zp2d_conv2d_3

    hls::stream<layer14_t> layer14_out("layer14_out");
    #pragma HLS STREAM variable=layer14_out depth=16
    nnet::conv_2d_cl<layer27_t, layer14_t, config14>(layer27_out, layer14_out, w14, b14); // conv2d_3

//    hls::stream<layer16_t> layer16_out("layer16_out");
    #pragma HLS STREAM variable=layer16_out depth=16
    nnet::relu<layer14_t, layer16_t, ReLU_config16>(layer14_out, layer16_out); // re_lu_3

}
