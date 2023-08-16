#ifndef GALAPAGOS_KERNEL_3_H_
#define GALAPAGOS_KERNEL_3_H_

#include "libGalapagos/galapagos_packet.h"
//#include "libGalapagos/galapagos_interface.hpp"
#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"
#include "defines.h"
#include "nnet_utils/nnet_helpers.h"
//#include "galapagos_interface.hpp"
//#include "galapagos_kernel.hpp"

#include "Kernel_3.h"
#include "Conversion.h"


void Galapagos_Kernel_3(
        short id,
        galapagos_interface *in, // Read-Only
        galapagos_interface *out       // Output Result
        );

#endif
