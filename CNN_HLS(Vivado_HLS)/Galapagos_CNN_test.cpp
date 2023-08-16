#include "Galapagos_CNN_test.h"

// hls-fpga-machine-learning insert bram

int main()
{
    // load input data from text file
    std::ifstream fin("tb_data/tb_input_features.dat");
    // load predictions from text file
    std::ifstream fpr("tb_data/tb_output_predictions.dat");

    std::string RESULTS_LOG = "tb_data/csim_results.log";

    std::ofstream fout(RESULTS_LOG);

    std::string iline;
    std::string pline;
    int e = 0;

    if (fin.is_open() && fpr.is_open())
    {
        while (std::getline(fin, iline) && std::getline(fpr, pline))
        {
            std::cout << "Processing input " << e << std::endl;
            char *cstr = const_cast<char *>(iline.c_str());
            char *current;
            std::vector<float> in;
            current = strtok(cstr, " ");
            while (current != NULL)
            {
                in.push_back(atof(current));
                current = strtok(NULL, " ");
            }
            cstr = const_cast<char *>(pline.c_str());
            std::vector<float> pr;
            current = strtok(cstr, " ");
            while (current != NULL)
            {
                pr.push_back(atof(current));
                current = strtok(NULL, " ");
            }

            // hls-fpga-machine-learning insert data
		    hls::stream<input_t> input_1("input_1");
		    hls::stream<result_t> layer27_out("layer27_out");
			nnet::copy_data<float, input_t, 0, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(in, input_1);

			// hls-fpga-machine-learning insert top-level-function
            auto *gp0 = new galapagos_interface;
            auto *gp1 = new galapagos_interface;
            auto *gp2 = new galapagos_interface;
            auto *gp3 = new galapagos_interface;

            hls_stream_to_galapagos<input_t, ap_fixed<32,8>, N_INPUT_1_1*N_INPUT_2_1, 64>(1, input_1, gp0);
            Galapagos_Kernel_1(2, gp0, gp1);
            Galapagos_Kernel_2(3, gp1, gp2);
            Galapagos_Kernel_3(4, gp2, gp3);
            galapagos_to_hls_stream<ap_fixed<32,8>, result_t, 1, 64>(gp3, layer27_out);

            delete gp0;
            delete gp1;
            delete gp2;
            delete gp3;

			std::cout << "Labels " << e << std::endl;
			// hls-fpga-machine-learning insert predictions
			for(int i = 0; i < N_LAYER_25; i++) {
			  std::cout << pr[i] << " ";
			}
			std::cout << std::endl;
			std::cout << "Predictions " << e << std::endl;
			// hls-fpga-machine-learning insert quantized
			nnet::print_result<result_t, N_LAYER_25>(layer27_out, std::cout, true);
            // hls-fpga-machine-learning insert tb-output
            nnet::print_result<result_t, N_LAYER_25>(layer27_out, fout);
            e++;
        }
        fin.close();
        fpr.close();
    } else {
        std::cout << "INFO: Unable to open input/predictions file, using default input." << std::endl;

//        // hls-fpga-machine-learning insert zero
//		hls::stream<input_t> input_1("input_1");
//		nnet::fill_zero<input_t, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(input_1);
//		hls::stream<result_t> layer27_out("layer27_out");
//
//        // hls-fpga-machine-learning insert top-level-function
//        CNN(input_1,layer27_out);
//
//        // hls-fpga-machine-learning insert output
//        nnet::print_result<result_t, N_LAYER_25>(layer27_out, std::cout, true);
//
//        // hls-fpga-machine-learning insert tb-output
//        nnet::print_result<result_t, N_LAYER_25>(layer27_out, fout);
    }

    fout.close();
    std::cout << "INFO: Saved inference results to file: " << RESULTS_LOG << std::endl;

    return 0;
}
