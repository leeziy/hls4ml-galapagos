#ifndef KERNEL_3_H_
#define KERNEL_3_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"

#include "defines.h"

// Prototype of top level function for C-synthesis
void Kernel_3(
    hls::stream<layer16_t> &layer16_out,
    hls::stream<result_t> &layer23_out
);

#endif
