#include "Galapagos_Kernel_3.h"

void Galapagos_Kernel_3(short id,
						galapagos_interface *in, // Read-Only
						galapagos_interface *out       // Output Result
){
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis register both port=out
	#pragma HLS INTERFACE axis register both port=in

	#pragma HLS DATAFLOW
	hls::stream<layer17_t> layer17_out("layer17_out");
	hls::stream<result_t> layer27_out("layer27_out");
	galapagos_to_hls_stream<ap_fixed<32, 8>, layer17_t, OUT_HEIGHT_17*OUT_WIDTH_17, 64>(in, layer17_out);
	Kernel_3(layer17_out, layer27_out);
    hls_stream_to_galapagos<result_t, ap_fixed<32, 8>, 1, 64>(id, layer27_out, out);
}
