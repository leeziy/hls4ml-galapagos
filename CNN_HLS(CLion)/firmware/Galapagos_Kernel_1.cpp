#include "Galapagos_Kernel_1.h"

void Galapagos_Kernel_1(short id,
						galapagos_interface *in, // Read-Only
						galapagos_interface *out       // Output Result
){
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis register both port=out
	#pragma HLS INTERFACE axis register both port=in

	#pragma HLS DATAFLOW
	hls::stream<input_t> input_1("input_1");
	hls::stream<layer9_t> layer9_out("layer9_out");
	galapagos_to_hls_stream<ap_fixed<32, 8>, input_t, N_INPUT_1_1*N_INPUT_2_1, 64>(in, input_1);
    Kernel_1(input_1, layer9_out);
	hls_stream_to_galapagos<layer9_t, ap_fixed<32, 8>, OUT_HEIGHT_9*OUT_WIDTH_9, 64>(id, layer9_out, out);
}
