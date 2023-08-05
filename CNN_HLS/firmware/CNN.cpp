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


    std::vector<std::string> kern_info_table;
    kern_info_table.push_back(std::string("127.0.0.1")); //kern 0 node address is 10.1.2.155
    kern_info_table.push_back(std::string("127.0.0.1")); //kern 1 node address is 10.1.2.155
    kern_info_table.push_back(std::string("127.0.0.1")); //kern 2 node address is 10.1.2.155
    kern_info_table.push_back(std::string("127.0.0.1")); //kern 3 node address is 10.1.2.155
    kern_info_table.push_back(std::string("127.0.0.1")); //kern 4 node address is 10.1.2.155
  

   
    galapagos::node<ap_uint <PACKET_DATA_LENGTH> > node0(kern_info_table, std::string("127.0.0.1"), std::vector<galapagos::external_driver <ap_uint<PACKET_DATA_LENGTH> > * >());


    node0.add_kernel(0, prepare_data_wrapper);
    node0.add_kernel(1, kernel1_wrapper);
    node0.add_kernel(2, kernel2_wrapper);
    node0.add_kernel(3, kernel3_wrapper);
    node0.add_kernel(4, validate_wrapper);


    node0.start();
    
    node0.end();


    // galapagos_interface tube(std::string("tube"));


    // hls_stream_2_galapagos_interface_wrapper<input_t>(input_1, &tube, N_INPUT_1_1 * N_INPUT_2_1, 1);
    // galapagos_interface_2_hls_stream_wrapper<input_t>(&tube, input_1, N_INPUT_1_1 * N_INPUT_2_1);
    // Kernel_1(input_1, layer9_out);
    
   
    // Kernel_2(layer9_out, layer16_out);

    // Kernel_3(layer16_out, layer23_out);
}

void prepare_data_wrapper(short id, galapagos_interface * in, galapagos_interface * out)
{
    std::cout<<"prepare data"<<std::endl;
    hls::stream<input_t> dataloader; 
    nnet::fill_zero<input_t, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(dataloader);
    std::cout<<"dataloader  size "<< dataloader.size()<<std::endl;
    hls_stream_2_galapagos_interface_wrapper<input_t>(dataloader, out, 1024, 0, 1, true);
    std::cout<<"send data to kernel 1"<<std::endl;
};


void kernel1_wrapper(short id, galapagos_interface * in, galapagos_interface * out)
{   
    hls::stream<input_t> input_1("input_1"); 
    hls::stream<layer9_t> layer9_out("layer9_out");
    
    galapagos_interface_2_hls_stream_wrapper<input_t>(in, input_1, 1024, true);
    std::cout<<"read data at kernel 1"<<std::endl;
    Kernel_1(input_1, layer9_out);
    std::cout<<"layer9_out data size "<< layer9_out.size()<<std::endl;
    hls_stream_2_galapagos_interface_wrapper<layer9_t>(layer9_out, out, OUT_HEIGHT_9 * OUT_WIDTH_9, 1, 2);
    std::cout<<"send data to kernel 2"<<std::endl;

};

void kernel2_wrapper(short id, galapagos_interface * in, galapagos_interface * out)
{   
    hls::stream<layer9_t> layer9_out("layer9_out");
    hls::stream<layer16_t> layer16_out("layer16_out");
    
    galapagos_interface_2_hls_stream_wrapper<layer9_t>(in, layer9_out, OUT_HEIGHT_9 * OUT_WIDTH_9);
    std::cout<<"read data at kernel 2, layer9_out data size "<< layer9_out.size()<<std::endl;
    Kernel_2(layer9_out, layer16_out);
    std::cout<<"layer16_out data size "<< layer16_out.size()<<std::endl;
    hls_stream_2_galapagos_interface_wrapper<layer16_t>(layer16_out, out, 16, 2, 3);
    std::cout<<"send data to kernel 3"<<std::endl;

};


void kernel3_wrapper(short id, galapagos_interface * in, galapagos_interface * out)
{   
    hls::stream<layer16_t> layer16_out("layer16_out");
    hls::stream<result_t> layer23_out("layer23_out");
    galapagos_interface_2_hls_stream_wrapper<layer16_t>(in, layer16_out, 16);
    std::cout<<"read data at kernel 3"<<std::endl;
    Kernel_3(layer16_out, layer23_out);
    std::cout<<"layer23_out data size "<< layer23_out.size()<<std::endl;
    hls_stream_2_galapagos_interface_wrapper<result_t>(layer23_out, out, 1, 3, 4);
    std::cout<<"send data for final validation"<<std::endl;
};

void validate_wrapper(short id, galapagos_interface * in, galapagos_interface * out)
{   
    hls::stream<result_t> layer23_out("layer23_out");
    galapagos_interface_2_hls_stream_wrapper<result_t>(in, layer23_out, 1);
    std::cout<<"read data for final validation"<<std::endl;
    nnet::print_result<result_t, N_LAYER_21>(layer23_out, std::cout, true);
};


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
