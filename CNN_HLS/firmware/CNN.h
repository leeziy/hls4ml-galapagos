#ifndef CNN_H_
#define CNN_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"

#include "defines.h"

#include "packet_size.h"
#ifdef CPU
#include "galapagos_interface.hpp"
#else
#include "galapagos_packet.h"
#endif

#include "galapagos_kernel.hpp"
#include "galapagos_local_router.hpp"
#include "galapagos_external_driver.hpp"
#include "galapagos_net_tcp.hpp"
#include "galapagos_node.hpp"

#include "nnet_utils/nnet_helpers.h"



// Prototype of top level function for C-synthesis
void CNN(
    hls::stream<input_t> &input_1,
    hls::stream<result_t> &layer23_out);

void Kernel_1(
    hls::stream<input_t> &input_1,
    hls::stream<layer9_t> &layer9_out);

void Kernel_2(
    hls::stream<layer9_t> &layer9_out,
    hls::stream<layer16_t> &layer16_out);

void Kernel_3(
    hls::stream<layer16_t> &layer16_out,
    hls::stream<result_t> &layer23_out);

// template <int NUM_STREAM, class D_TYPE>
// void hls_stream_2_galapagos_interface_wrapper(
//     hls::stream<D_TYPE> in[NUM_STREAM],
//     galapagos::interface<D_TYPE> * out,
//     int elements_in_stream
//     );

// width determins the shape of packets in hls stream
// size determins the number of packets to be delivered in hls stream
template <class STREAM_TYPE>
void hls_stream_2_galapagos_interface_wrapper(
    hls::stream<STREAM_TYPE> & hls_output,
    galapagos_interface * bridge_output,
    int elements_in_stream,
    const int id,
    const int dest, 
    bool debug = false)
{
    galapagos_packet packet;
    packet.id = id;
    packet.last = 0;
    packet.dest = dest;
    // packet.user = 0; // not quite sure the usage of this part

    int GP_TRANSFER_SIZE = PACKET_DATA_LENGTH / BASE_TYPE_LEN;
    int STREAM_OUTER_LOOP_SIZE = STREAM_TYPE::size / GP_TRANSFER_SIZE;
    for (int i = 0; i < elements_in_stream; i++)
    {
#pragma HLS pipeline II = 1
        if (!hls_output.empty())
        {
            auto hls_data = hls_output.read();
            for (int j = 0; j < STREAM_OUTER_LOOP_SIZE; j++)
            {
                for(int k = 0; k < GP_TRANSFER_SIZE; k++)
                {
                    packet.data.range((k + 1) * BASE_TYPE_LEN - 1, (k)*BASE_TYPE_LEN) \
                    = hls_data[j * GP_TRANSFER_SIZE + k].range();
                }
                packet.last = ((i == (elements_in_stream - 1)) && j == (STREAM_OUTER_LOOP_SIZE - 1));
                bridge_output->write(packet);
            }
            
        }
    }
    if(debug == true)
    {
        std::cout<<bridge_output->size()<<std::endl;
    }
};


template <class STREAM_TYPE>
void galapagos_interface_2_hls_stream_wrapper(
    galapagos_interface * bridge_input,
    hls::stream<STREAM_TYPE> & hls_input,
    int elements_in_stream, 
    bool debug = false)
{
    galapagos_packet packet;

    int GP_TRANSFER_SIZE = PACKET_DATA_LENGTH / BASE_TYPE_LEN;
    int STREAM_OUTER_LOOP_SIZE = STREAM_TYPE::size / GP_TRANSFER_SIZE;

    for (int i = 0; i < elements_in_stream; i++)
    {
        if(debug == true) std::cout<<i <<std::endl;
#pragma HLS pipeline II = 1
        // while(!bridge_input->empty())
        {
            STREAM_TYPE hls_data;
            // for (int j = 0; j < STREAM_TYPE::size; j++)
            for (int j = 0; j < STREAM_OUTER_LOOP_SIZE; j++)
            {
                packet = bridge_input->read();
                for(int k = 0; k < GP_TRANSFER_SIZE; k++)
                {
                    hls_data[j * GP_TRANSFER_SIZE + k].range() = packet.data.range((k + 1) * BASE_TYPE_LEN - 1, (k)*BASE_TYPE_LEN);
                }
            }
            hls_input.write(hls_data);
        }
    }
};


void prepare_data_wrapper(short id, galapagos_interface * in, galapagos_interface * out);
void kernel1_wrapper(short id, galapagos_interface * in, galapagos_interface * out);
void kernel2_wrapper(short id, galapagos_interface * in, galapagos_interface * out);
void kernel3_wrapper(short id, galapagos_interface * in, galapagos_interface * out);
void validate_wrapper(short id, galapagos_interface * in, galapagos_interface * out);
// void kernel1_4_galapagos(short id, galapagos_interface * in, galapagos_interface * out){
    
  


    
//     galapagos_interface_2_hls_stream_wrapper<input_t>(&tube, input_1, N_INPUT_1_1 * N_INPUT_2_1);
//     Kernel_1(input_1, layer9_out);

//     generate_flit(NUM_ITERATIONS, MAX_BUFFER, id, id+1, out);
// }



#endif
