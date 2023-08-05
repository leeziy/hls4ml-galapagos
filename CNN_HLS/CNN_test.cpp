#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "setup.h"

#include "firmware/CNN.h"
#include "firmware/nnet_utils/nnet_helpers.h"

////////////////////////////////////////////////////
typedef ap_fixed<16,6> base_t;
////////////////////////////////////////////////////
// hls-fpga-machine-learning insert bram

#define CHECKPOINT 5000

namespace nnet {
bool trace_enabled = true;
std::map<std::string, void *> *trace_outputs = NULL;
size_t trace_type_size = sizeof(double);
} // namespace nnet

int main(int argc, char **argv) {
    setupEnvironment();
#ifdef VALIDATE
    // load input data from text file
    std::ifstream fin("tb_data/tb_input_features.dat");
    // load predictions from text file
    std::ifstream fpr("tb_data/tb_output_predictions.dat");
#else
    std::ifstream fin("open_nothing");
    // load predictions from text file
    std::ifstream fpr("open_nothing");
#endif

#ifdef RTL_SIM
    std::string RESULTS_LOG = "tb_data/rtl_cosim_results.log";
#else
    std::string RESULTS_LOG = "tb_data/csim_results.log";
#endif
    std::ofstream fout(RESULTS_LOG);

    std::string iline;
    std::string pline;
    int e = 0;

    if (fin.is_open() && fpr.is_open()) {
        while (std::getline(fin, iline) && std::getline(fpr, pline)) {
            if (e % CHECKPOINT == 0)
                std::cout << "Processing input " << e << std::endl;
            char *cstr = const_cast<char *>(iline.c_str());
            char *current;
            std::vector<float> in;
            current = strtok(cstr, " ");
            while (current != NULL) {
                in.push_back(atof(current));
                current = strtok(NULL, " ");
            }
            cstr = const_cast<char *>(pline.c_str());
            std::vector<float> pr;
            current = strtok(cstr, " ");
            while (current != NULL) {
                pr.push_back(atof(current));
                current = strtok(NULL, " ");
            }

            // hls-fpga-machine-learning insert data
    // RE(ZJN): note that the stream we use here is only 1 dim, not parallel streams
    // TODO: generate paralell streams
    // MOD: turn hls::stream<input_t> input_1("input_1") to hls::stream<input_t> input_1[1]
        hls::stream<input_t> input_1; 
        nnet::copy_data<float, input_t, 0, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(in, input_1);
        // galapagos::interface<input_t> out(std::string("out"));
        // hls_stream_2_galapagos_interface_wrapper<1, input_t>(input_1, out, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1);
        // hls_stream_2_galapagos_interface_wrapper<1, input_t>(input_1, &out, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1);


      hls::stream<result_t> layer23_out("layer23_out");

            // hls-fpga-machine-learning insert top-level-function
            CNN(input_1,layer23_out);

            if (e % CHECKPOINT == 0) {
                std::cout << "Predictions" << std::endl;
                // hls-fpga-machine-learning insert predictions
                for(int i = 0; i < N_LAYER_21; i++) {
                  std::cout << pr[i] << " ";
                }
                std::cout << std::endl;
                std::cout << "Quantized predictions" << std::endl;
                // hls-fpga-machine-learning insert quantized
                nnet::print_result<result_t, N_LAYER_21>(layer23_out, std::cout, true);
            }
            e++;

            // hls-fpga-machine-learning insert tb-output
            nnet::print_result<result_t, N_LAYER_21>(layer23_out, fout);
        }
        fin.close();
        fpr.close();
    } else {
        std::cout << "INFO: Unable to open input/predictions file, using default input." << std::endl;

        // hls-fpga-machine-learning insert zero
    hls::stream<input_t> input_1; 

    // int testcases = 12;
    // N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1
    
    // nnet::fill_rand<input_t, 9>(input_1);
    nnet::fill_zero<input_t, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(input_1);


    // galapagos::interface<input_t_gp> out(std::string("out"));
    // // std::cout<<"1"<<std::endl;
    // hls_stream_2_galapagos_interface_wrapper<input_t, input_t_gp>(input_1, &out, 3, 1);
    // // std::cout<<"2"<<std::endl;
    // galapagos_interface_2_hls_stream_wrapper<input_t, input_t_gp>(&out, input_1, 3);
    // // std::cout<<"3"<<std::endl;
    


    




    hls::stream<result_t> layer23_out("layer23_out");

        // hls-fpga-machine-learning insert top-level-function
        CNN(input_1,layer23_out);

        // hls-fpga-machine-learning insert output
        // nnet::print_result<result_t, N_LAYER_21>(layer23_out, std::cout, true);

        // hls-fpga-machine-learning insert tb-output
        // nnet::print_result<result_t, N_LAYER_21>(layer23_out, fout);
    }

    fout.close();
    std::cout << "INFO: Saved inference results to file: " << RESULTS_LOG << std::endl;

    return 0;
}
