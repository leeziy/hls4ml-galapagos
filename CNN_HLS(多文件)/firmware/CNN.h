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

#endif
