#ifndef GALAPAGOS_BRIDGE_H
#define GALAPAGOS_BRIDGE_H

#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"

#include "packet_size.h"
#ifdef CPU
#include "galapagos_interface.hpp"
#else
#include "galapagos_packet.h"
#endif




template<int width, class OUTPUT_T>
void hls4ml_galapagos_output_bridge (
                                    ap_uint<16> size,
                                    hls::stream<OUTPUT_T> output[width],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest)
{


    _hls4ml_galapagos_output_bridge<width, OUTPUT_T>(size, output, bridge_output, dest);

};


#endif