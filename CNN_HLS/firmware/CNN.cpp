#include <iostream>

#include "CNN.h"
#include "parameters.h"



void CNN(
    hls::stream<input_t> &input_1,
    hls::stream<result_t> &layer23_out)
{

// hls-fpga-machine-learning insert IO
#pragma HLS INTERFACE axis port = input_1, layer23_out
#pragma HLS DATAFLOW

#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights)
    {
        // hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<conv2d_default_t, 1728>(w2, "w2.txt");
        nnet::load_weights_from_txt<conv2d_default_t, 64>(b2, "b2.txt");
        nnet::load_weights_from_txt<conv2d_1_default_t, 36864>(w6, "w6.txt");
        nnet::load_weights_from_txt<conv2d_1_default_t, 64>(b6, "b6.txt");
        nnet::load_weights_from_txt<conv2d_2_default_t, 36864>(w10, "w10.txt");
        nnet::load_weights_from_txt<conv2d_2_default_t, 64>(b10, "b10.txt");
        nnet::load_weights_from_txt<conv2d_3_default_t, 36864>(w14, "w14.txt");
        nnet::load_weights_from_txt<conv2d_3_default_t, 64>(b14, "b14.txt");
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

    hls::stream<layer9_t> layer9_out("layer9_out");
    hls::stream<layer16_t> layer16_out("layer16_out");

    Kernel_1(input_1, layer9_out);

    Kernel_2(layer9_out, layer16_out);

    Kernel_3(layer16_out, layer23_out);
}

// template <int packet_num, int width, int index_offset, class D_TYPE>
// void _hls4ml_galapagos_output_bridge_read_words(
//     bool reset,
//     galapagos_packet &gp_out,
//     hls::stream<D_TYPE> output[width])
// {

//     for (int j = 0; j < packet_num; j++)
//     {
//         // we need to add some assertions on output boundaries
// #pragma HLS pipeline II = 1
//         if (!output[j + index_offset].empty())
//         {
//             D_TYPE packet;
//             packet = output[j + index_offset].read();
//             if (reset)
//             {
//                 if (j == 0)
//                     gp_out.data(0, 0) = packet.id.range();
//                 gp_out.data.range((j + 1) * 8 + 7, (j + 1) * 8) = packet.data.range();
//             }
//             else
//                 gp_out.data.range((j)*8 + 7, (j)*8) = packet.data.range();
//         }
//     }
// }

// width determins the shape of packets in hls stream
// size determins the number of packets to be delivered in hls stream
template <int width, class D_TYPE>
void hls4ml_galapagos_output_bridge(
    ap_uint<16> size,
    hls::stream<D_TYPE> hls_output[width],
    galapagos_interface *bridge_output,
    const ap_uint<8> dest)
{

    galapagos_packet packet;
    packet.last = 0;
    packet.dest = dest;
    packet.user = 0; // not quite sure the usage of this part

    const int D_TYPE_LEN = sizeof(D_TYPE);

    // continue to deliver data from hls to galapagos interface
    for (int i = 0; i < (size - 1); i++)
    {
        for (int j = 0; j < width; j++)
        {
#pragma HLS pipeline II = 1
            D_TYPE data;
            if (!hls_output[j].empty())
            {
                data.range() = hls_output[j].read().range();
                packet.data.range((j + 1) * D_TYPE_LEN - 1, (j)*D_TYPE_LEN) = data.range();
            }
        }
        packet.last = 0;
        bridge_output->write(packet);
    }

    // handle remaining parts, then end the transmission
    for (int j = 0; j < width; j++)
    {
#pragma HLS pipeline II = 1
        D_TYPE data;
        if (!hls_output[j].empty())
        {
            data.range() = hls_output[j].read().range();
            packet.data.range((j + 1) * D_TYPE_LEN - 1, (j)*D_TYPE_LEN) = data.range();
        }
    }

    packet.last = 1; // informing galapagos interface the end of transmission
    bridge_output->write(packet);
}


// void hls4ml_galapagos_output_bridge(
//     ap_uint<32> size,
//     hls::stream<D_TYPE> hls_output[width],
//     galapagos_interface *bridge_output,
//     const ap_uint<8> dest)

// template <int NUM_STREAM, class D_TYPE>
// void hls_stream_2_galapagos_interface_wrapper(
//     hls::stream<D_TYPE> in[NUM_STREAM],
//     galapagos::interface<D_TYPE> * out,
//     int elements_in_stream
//     )
// {
//     // hls4ml_galapagos_output_bridge <3> ((ap_uint<16>) 1, input, out, 1);
// }

void galapagos_interface_2_hls_stream(
    galapagos_interface *in,
    hls::stream<result_t> &out)
{
}

void galapagos_kernel_wrapper(
    short id, // for routing purpose
    galapagos_interface *in,
    galapagos_interface *out)
{
}

void Kernel_1(
    hls::stream<input_t> &input_1,
    hls::stream<layer9_t> &layer9_out)
{
// hls-fpga-machine-learning insert IO
#pragma HLS INTERFACE axis port = input_1, layer9_out
#pragma HLS DATAFLOW

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    hls::stream<layer24_t> layer24_out("layer24_out");
#pragma HLS STREAM variable = layer24_out depth = 1156
    nnet::zeropad2d_cl<input_t, layer24_t, config24>(input_1, layer24_out); // zp2d_conv2d

    hls::stream<layer2_t> layer2_out("layer2_out");
#pragma HLS STREAM variable = layer2_out depth = 1024
    nnet::conv_2d_cl<layer24_t, layer2_t, config2>(layer24_out, layer2_out, w2, b2); // conv2d

    hls::stream<layer4_t> layer4_out("layer4_out");
#pragma HLS STREAM variable = layer4_out depth = 1024
    nnet::relu<layer2_t, layer4_t, ReLU_config4>(layer2_out, layer4_out); // re_lu

    hls::stream<layer5_t> layer5_out("layer5_out");
#pragma HLS STREAM variable = layer5_out depth = 256
    nnet::pooling2d_cl<layer4_t, layer5_t, config5>(layer4_out, layer5_out); // max_pooling2d

    hls::stream<layer25_t> layer25_out("layer25_out");
#pragma HLS STREAM variable = layer25_out depth = 324
    nnet::zeropad2d_cl<layer5_t, layer25_t, config25>(layer5_out, layer25_out); // zp2d_conv2d_1

    hls::stream<layer6_t> layer6_out("layer6_out");
#pragma HLS STREAM variable = layer6_out depth = 256
    nnet::conv_2d_cl<layer25_t, layer6_t, config6>(layer25_out, layer6_out, w6, b6); // conv2d_1

    hls::stream<layer8_t> layer8_out("layer8_out");
#pragma HLS STREAM variable = layer8_out depth = 256
    nnet::relu<layer6_t, layer8_t, ReLU_config8>(layer6_out, layer8_out); // re_lu_1

    //    hls::stream<layer9_t> layer9_out("layer9_out");
#pragma HLS STREAM variable = layer9_out depth = 64
    nnet::pooling2d_cl<layer8_t, layer9_t, config9>(layer8_out, layer9_out); // max_pooling2d_1
}

void Kernel_2(
    hls::stream<layer9_t> &layer9_out,
    hls::stream<layer16_t> &layer16_out)
{
// hls-fpga-machine-learning insert IO
#pragma HLS INTERFACE axis port = layer9_out, layer16_out
#pragma HLS DATAFLOW

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    hls::stream<layer26_t> layer26_out("layer26_out");
#pragma HLS STREAM variable = layer26_out depth = 100
    nnet::zeropad2d_cl<layer9_t, layer26_t, config26>(layer9_out, layer26_out); // zp2d_conv2d_2

    hls::stream<layer10_t> layer10_out("layer10_out");
#pragma HLS STREAM variable = layer10_out depth = 64
    nnet::conv_2d_cl<layer26_t, layer10_t, config10>(layer26_out, layer10_out, w10, b10); // conv2d_2

    hls::stream<layer12_t> layer12_out("layer12_out");
#pragma HLS STREAM variable = layer12_out depth = 64
    nnet::relu<layer10_t, layer12_t, ReLU_config12>(layer10_out, layer12_out); // re_lu_2

    hls::stream<layer13_t> layer13_out("layer13_out");
#pragma HLS STREAM variable = layer13_out depth = 16
    nnet::pooling2d_cl<layer12_t, layer13_t, config13>(layer12_out, layer13_out); // max_pooling2d_2

    hls::stream<layer27_t> layer27_out("layer27_out");
#pragma HLS STREAM variable = layer27_out depth = 36
    nnet::zeropad2d_cl<layer13_t, layer27_t, config27>(layer13_out, layer27_out); // zp2d_conv2d_3

    hls::stream<layer14_t> layer14_out("layer14_out");
#pragma HLS STREAM variable = layer14_out depth = 16
    nnet::conv_2d_cl<layer27_t, layer14_t, config14>(layer27_out, layer14_out, w14, b14); // conv2d_3

    //    hls::stream<layer16_t> layer16_out("layer16_out");
#pragma HLS STREAM variable = layer16_out depth = 16
    nnet::relu<layer14_t, layer16_t, ReLU_config16>(layer14_out, layer16_out); // re_lu_3
}

void Kernel_3(
    hls::stream<layer16_t> &layer16_out,
    hls::stream<result_t> &layer23_out)
{
// hls-fpga-machine-learning insert IO
#pragma HLS INTERFACE axis port = layer16_out, layer23_out
#pragma HLS DATAFLOW

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    auto &layer17_out = layer16_out;
    hls::stream<layer18_t> layer18_out("layer18_out");
#pragma HLS STREAM variable = layer18_out depth = 1
    nnet::dense<layer16_t, layer18_t, config18>(layer17_out, layer18_out, w18, b18); // dense

    hls::stream<layer20_t> layer20_out("layer20_out");
#pragma HLS STREAM variable = layer20_out depth = 1
    nnet::relu<layer18_t, layer20_t, ReLU_config20>(layer18_out, layer20_out); // re_lu_4

    hls::stream<layer21_t> layer21_out("layer21_out");
#pragma HLS STREAM variable = layer21_out depth = 1
    nnet::dense<layer20_t, layer21_t, config21>(layer20_out, layer21_out, w21, b21); // dense_1

    nnet::softmax<layer21_t, result_t, Softmax_config23>(layer21_out, layer23_out); // softmax
}
