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


// Prototype of top level function for C-synthesis
void CNN(
    hls::stream<input_t> &input_1,
    hls::stream<result_t> &layer23_out
);

void Kernel_1(
    hls::stream<input_t> &input_1,
    hls::stream<layer9_t> &layer9_out
);

void Kernel_2(
    hls::stream<layer9_t> &layer9_out,
    hls::stream<layer16_t> &layer16_out
);

void Kernel_3(
    hls::stream<layer16_t> &layer16_out,
    hls::stream<result_t> &layer23_out
);


// template <int NUM_STREAM, class D_TYPE>
// void hls_stream_2_galapagos_interface_wrapper(
//     hls::stream<D_TYPE> in[NUM_STREAM],
//     galapagos::interface<D_TYPE> * out,
//     int elements_in_stream
//     );

template <int NUM_STREAM, class D_TYPE>
void hls_stream_2_galapagos_interface_wrapper(
    hls::stream<D_TYPE> in[NUM_STREAM],
    galapagos::interface<D_TYPE> * out,
    int elements_in_stream
    )
    {
        
    };

#endif
