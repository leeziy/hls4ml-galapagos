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
#define OUT_HEIGHT_24 34
#define OUT_WIDTH_24 34
#define N_CHAN_24 3
#define OUT_HEIGHT_2 32
#define OUT_WIDTH_2 32
#define N_FILT_2 64
#define OUT_HEIGHT_2 32
#define OUT_WIDTH_2 32
#define N_FILT_2 64
#define OUT_HEIGHT_5 16
#define OUT_WIDTH_5 16
#define N_FILT_5 64
#define OUT_HEIGHT_25 18
#define OUT_WIDTH_25 18
#define N_CHAN_25 64
#define OUT_HEIGHT_6 16
#define OUT_WIDTH_6 16
#define N_FILT_6 64
#define OUT_HEIGHT_6 16
#define OUT_WIDTH_6 16
#define N_FILT_6 64
#define OUT_HEIGHT_9 8
#define OUT_WIDTH_9 8
#define N_FILT_9 64
#define OUT_HEIGHT_26 10
#define OUT_WIDTH_26 10
#define N_CHAN_26 64
#define OUT_HEIGHT_10 8
#define OUT_WIDTH_10 8
#define N_FILT_10 64
#define OUT_HEIGHT_10 8
#define OUT_WIDTH_10 8
#define N_FILT_10 64
#define OUT_HEIGHT_13 4
#define OUT_WIDTH_13 4
#define N_FILT_13 64
#define OUT_HEIGHT_27 6
#define OUT_WIDTH_27 6
#define N_CHAN_27 64
#define OUT_HEIGHT_14 4
#define OUT_WIDTH_14 4
#define N_FILT_14 64
#define OUT_HEIGHT_14 4
#define OUT_WIDTH_14 4
#define N_FILT_14 64
#define N_SIZE_0_17 1024
#define N_LAYER_18 128
#define N_LAYER_18 128
#define N_LAYER_21 10
#define N_LAYER_21 10

// hls-fpga-machine-learning insert layer-precision
typedef nnet::array<ap_fixed<16,6>, 3*1> input_t;
typedef nnet::array<ap_fixed<16,6>, 3*1> layer24_t;
typedef ap_fixed<16,6> conv2d_default_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer2_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer4_t;
typedef ap_fixed<18,8> re_lu_table_t;
typedef ap_fixed<16,8> max_pooling2d_default_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer5_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer25_t;
typedef ap_fixed<16,6> conv2d_1_default_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer6_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer8_t;
typedef ap_fixed<18,8> re_lu_1_table_t;
typedef ap_fixed<16,8> max_pooling2d_1_default_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer9_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer26_t;
typedef ap_fixed<16,6> conv2d_2_default_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer10_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer12_t;
typedef ap_fixed<18,8> re_lu_2_table_t;
typedef ap_fixed<16,8> max_pooling2d_2_default_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer13_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer27_t;
typedef ap_fixed<16,6> conv2d_3_default_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer14_t;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer16_t;
typedef ap_fixed<18,8> re_lu_3_table_t;
typedef ap_fixed<16,6> dense_default_t;
typedef nnet::array<ap_fixed<16,6>, 128*1> layer18_t;
typedef ap_uint<1> layer18_index;
typedef nnet::array<ap_fixed<16,6>, 128*1> layer20_t;
typedef ap_fixed<18,8> re_lu_4_table_t;
typedef ap_fixed<16,6> dense_1_default_t;
typedef nnet::array<ap_fixed<16,6>, 10*1> layer21_t;
typedef ap_uint<1> layer21_index;
typedef nnet::array<ap_fixed<16,6>, 10*1> result_t;
typedef ap_fixed<18,8> softmax_table_t;
typedef ap_fixed<18,8,AP_RND,AP_SAT> softmax_exp_table_t;
typedef ap_fixed<18,8,AP_RND,AP_SAT> softmax_inv_table_t;

#endif
