#include "Galapagos_Kernel_Input.h"

void Galapagos_Kernel_Input(short id,
						galapagos_interface *in, // Read-Only
						galapagos_interface *out       // Output Result
){
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis register both port=out
	#pragma HLS INTERFACE axis register both port=in

    // load input data from text file
    std::ifstream fin("tb_data/tb_input_features.dat");

    std::string iline;

    if (fin.is_open())
    {
		std::getline(fin, iline);
		std::cout << "Processing input " << std::endl;
		char *cstr = const_cast<char *>(iline.c_str());
		char *current;
		std::vector<float> in;
		current = strtok(cstr, " ");
		while (current != NULL)
		{
			in.push_back(atof(current));
			current = strtok(NULL, " ");
		}
		// hls-fpga-machine-learning insert data
		hls::stream<input_t> input_1("input_1");
		nnet::copy_data<float, input_t, 0, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(in, input_1);
		hls_stream_to_galapagos<input_t, ap_fixed<32, 8>, 64>(1, input_1, out);
    }
}
