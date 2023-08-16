#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

// hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 32
#define N_INPUT_2_1 32
#define N_INPUT_3_1 3
#define OUT_HEIGHT_28 34
#define OUT_WIDTH_28 34
#define N_CHAN_28 3
#define OUT_HEIGHT_2 32
#define OUT_WIDTH_2 32
#define N_FILT_2 64
#define OUT_HEIGHT_2 32
#define OUT_WIDTH_2 32
#define N_FILT_2 64
#define OUT_HEIGHT_5 16
#define OUT_WIDTH_5 16
#define N_FILT_5 64
#define OUT_HEIGHT_29 18
#define OUT_WIDTH_29 18
#define N_CHAN_29 64
#define OUT_HEIGHT_6 16
#define OUT_WIDTH_6 16
#define N_FILT_6 64
#define OUT_HEIGHT_6 16
#define OUT_WIDTH_6 16
#define N_FILT_6 64
#define OUT_HEIGHT_9 8
#define OUT_WIDTH_9 8
#define N_FILT_9 64
#define OUT_HEIGHT_30 10
#define OUT_WIDTH_30 10
#define N_CHAN_30 64
#define OUT_HEIGHT_10 8
#define OUT_WIDTH_10 8
#define N_FILT_10 64
#define OUT_HEIGHT_10 8
#define OUT_WIDTH_10 8
#define N_FILT_10 64
#define OUT_HEIGHT_13 4
#define OUT_WIDTH_13 4
#define N_FILT_13 64
#define OUT_HEIGHT_31 6
#define OUT_WIDTH_31 6
#define N_CHAN_31 64
#define OUT_HEIGHT_14 4
#define OUT_WIDTH_14 4
#define N_FILT_14 64
#define OUT_HEIGHT_14 4
#define OUT_WIDTH_14 4
#define N_FILT_14 64
#define OUT_HEIGHT_17 2
#define OUT_WIDTH_17 2
#define N_FILT_17 64
#define OUT_HEIGHT_32 4
#define OUT_WIDTH_32 4
#define N_CHAN_32 64
#define OUT_HEIGHT_18 2
#define OUT_WIDTH_18 2
#define N_FILT_18 64
#define OUT_HEIGHT_18 2
#define OUT_WIDTH_18 2
#define N_FILT_18 64
#define N_SIZE_0_21 256
#define N_LAYER_22 32
#define N_LAYER_22 32
#define N_LAYER_25 10
#define N_LAYER_25 10

// hls-fpga-machine-learning insert layer-precision
typedef nnet::array<ap_fixed<32,8>, 3*1> input_t;
typedef nnet::array<ap_fixed<32,8>, 3*1> layer28_t;
typedef ap_fixed<32,8> conv2d_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer2_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer4_t;
typedef ap_fixed<18,8> re_lu_table_t;
typedef ap_fixed<32,10> max_pooling2d_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer5_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer29_t;
typedef ap_fixed<32,8> conv2d_1_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer6_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer8_t;
typedef ap_fixed<18,8> re_lu_1_table_t;
typedef ap_fixed<32,10> max_pooling2d_1_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer9_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer30_t;
typedef ap_fixed<32,8> conv2d_2_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer10_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer12_t;
typedef ap_fixed<18,8> re_lu_2_table_t;
typedef ap_fixed<32,10> max_pooling2d_2_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer13_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer31_t;
typedef ap_fixed<32,8> conv2d_3_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer14_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer16_t;
typedef ap_fixed<18,8> re_lu_3_table_t;
typedef ap_fixed<32,10> max_pooling2d_3_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer17_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer32_t;
typedef ap_fixed<32,8> conv2d_4_default_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer18_t;
typedef nnet::array<ap_fixed<32,8>, 64*1> layer20_t;
typedef ap_fixed<18,8> re_lu_4_table_t;
typedef ap_fixed<32,8> dense_default_t;
typedef nnet::array<ap_fixed<32,8>, 32*1> layer22_t;
typedef ap_uint<1> layer22_index;
typedef nnet::array<ap_fixed<32,8>, 32*1> layer24_t;
typedef ap_fixed<18,8> re_lu_5_table_t;
typedef ap_fixed<32,8> dense_1_default_t;
typedef nnet::array<ap_fixed<32,8>, 10*1> layer25_t;
typedef ap_uint<1> layer25_index;
typedef nnet::array<ap_fixed<32,8>, 10*1> result_t;
typedef ap_fixed<18,8> softmax_table_t;
typedef ap_fixed<18,8,AP_RND,AP_SAT> softmax_exp_table_t;
typedef ap_fixed<18,8,AP_RND,AP_SAT> softmax_inv_table_t;

#endif
