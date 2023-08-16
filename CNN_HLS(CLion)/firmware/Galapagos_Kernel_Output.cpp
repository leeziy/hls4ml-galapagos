#include "Galapagos_Kernel_Output.h"

void Galapagos_Kernel_Output(short id,
						galapagos_interface *in, // Read-Only
						galapagos_interface *out       // Output Result
){
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis register both port=out
	#pragma HLS INTERFACE axis register both port=in

    // load predictions from text file
    std::ifstream fpr("tb_data/tb_output_predictions.dat");

	#ifdef RTL_SIM
		std::string RESULTS_LOG = "tb_data/rtl_cosim_results.log";
	#else
		std::string RESULTS_LOG = "tb_data/csim_results.log";
	#endif
		std::ofstream fout(RESULTS_LOG);

    std::string pline;

    if (fpr.is_open())
    {
		std::getline(fpr, pline);
		std::cout << "Processing input " << std::endl;
		char *cstr = const_cast<char *>(pline.c_str());
		std::vector<float> pr;
		char *current = strtok(cstr, " ");
		while (current != NULL)
		{
			pr.push_back(atof(current));
			current = strtok(NULL, " ");
		}
		// hls-fpga-machine-learning insert data
		hls::stream<result_t> layer27_out("layer27_out");
		galapagos_to_hls_stream<ap_fixed<32, 8>, result_t, 64>(out, layer27_out);
		std::cout << "Labels " << std::endl;
		// hls-fpga-machine-learning insert predictions
		for(int i = 0; i < N_LAYER_25; i++) {
		  std::cout << pr[i] << " ";
		}
		std::cout << std::endl;
		std::cout << "Predictions " << std::endl;
		// hls-fpga-machine-learning insert quantized
		nnet::print_result<result_t, N_LAYER_25>(layer27_out, std::cout, true);
        // hls-fpga-machine-learning insert tb-output
        nnet::print_result<result_t, N_LAYER_25>(layer27_out, fout);
    }
}
