#include "Galapagos_Kernel_2.h"

void Galapagos_Kernel_2(short id,
						galapagos_interface *in, // Read-Only
						galapagos_interface *out       // Output Result
){
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis register both port=out
	#pragma HLS INTERFACE axis register both port=in

	#pragma HLS DATAFLOW
	hls::stream<layer9_t> layer9_out("layer9_out");
	hls::stream<layer17_t> layer17_out("layer17_out");
	galapagos_to_hls_stream<ap_fixed<32, 8>, layer9_t, OUT_HEIGHT_9*OUT_WIDTH_9, 64>(in, layer9_out);
	Kernel_2(layer9_out, layer17_out);
    hls_stream_to_galapagos<layer17_t, ap_fixed<32, 8>, OUT_HEIGHT_17*OUT_WIDTH_17, 64>(id, layer17_out, out);
}
