#ifndef KERNEL_1_H_
#define KERNEL_1_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"

#include "defines.h"

// Prototype of top level function for C-synthesis
void Kernel_1(
    hls::stream<input_t> &input_1,
    hls::stream<layer9_t> &layer9_out
);

#endif
