#ifndef CNN_H_
#define CNN_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"

#include "defines.h"

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

#endif
