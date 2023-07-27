import hls4ml
import plotting
import keras
import os

os.environ["PATH"] += os.pathsep + "/home/leeziy/software/Xilinx/Vivado/2019.2/bin"

network = keras.models.load_model('CNN.h5')
network.summary()

hls_config = hls4ml.utils.config_from_keras_model(network, granularity='name')
hls_config['Model']['Precision'] = 'ap_fixed<16,6>'
hls_config['Model']['Strategy'] = 'Resource'
for Layer in hls_config['LayerName'].keys():
    hls_config['LayerName'][Layer]['Precision'] = 'ap_fixed<16,6>'
    hls_config['LayerName'][Layer]['Strategy'] = 'Resource'
    try:
        params_num = network.get_layer(Layer).count_params()
        if params_num > 64:
            reuse_factor = int(params_num / 64)
            hls_config['LayerName'][Layer]['ReuseFactor'] = reuse_factor
    except ValueError:
        pass
plotting.print_dict(hls_config)

hls_model = hls4ml.converters.convert_from_keras_model(network, io_type='io_stream', backend='Vivado',
                                                       output_dir='CNN_HLS', project_name='CNN',
                                                       part='xcvu35p-fsvh2104-1-e', hls_config=hls_config)
# hls4ml.utils.plot_model(hls_model, to_file=None, show_shapes=True, show_layer_names=True, show_precision=True)
hls_model.build(reset=False, csim=False, synth=False, cosim=False,
                validation=False, export=False, vsynth=False, fifo_opt=False)
