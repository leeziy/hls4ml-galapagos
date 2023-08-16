#ifndef GALAPAGOS_KERNEL_OUTPUT_H_
#define GALAPAGOS_KERNEL_OUTPUT_H_

#include "libGalapagos/galapagos_packet.h"
//#include "libGalapagos/galapagos_interface.hpp"
#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"
#include "defines.h"
#include "nnet_utils/nnet_helpers.h"
//#include "galapagos_interface.hpp"
//#include "galapagos_kernel.hpp"
#include "Conversion.h"


void Galapagos_Kernel_Output(
        short id,
        galapagos_interface *in, // Read-Only
        galapagos_interface *out       // Output Result
        );

#endif
