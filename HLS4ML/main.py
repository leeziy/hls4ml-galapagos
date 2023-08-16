import hls4ml
import tensorflow
import plotting
import keras
import os
import numpy
from read_binary import cifar10_unbatch

os.environ["PATH"] += os.pathsep + "/home/leeziy/software/Xilinx/Vivado/2019.2/bin"

# train_images = []
# train_labels = []
# test_images = []
# test_labels = []
# cifar10_unbatch(file="data_batch_1.bin", feature_output=train_images, label_output=train_labels)
# cifar10_unbatch(file="data_batch_2.bin", feature_output=train_images, label_output=train_labels)
# cifar10_unbatch(file="data_batch_3.bin", feature_output=train_images, label_output=train_labels)
# cifar10_unbatch(file="data_batch_4.bin", feature_output=train_images, label_output=train_labels)
# cifar10_unbatch(file="data_batch_5.bin", feature_output=train_images, label_output=train_labels)
# cifar10_unbatch(file="test_batch.bin", feature_output=test_images, label_output=test_labels)
# train_images = numpy.stack(train_images)
# train_labels = numpy.stack(train_labels)
# test_images = numpy.stack(test_images)
# test_labels = numpy.stack(test_labels)
# print(test_images.shape)

network = keras.models.load_model('CNN.h5')
network.summary()

hls_config = hls4ml.utils.config_from_keras_model(network, granularity='name')
hls_config['Model']['Precision'] = 'ap_fixed<32,8>'
hls_config['Model']['Strategy'] = 'Resource'
for Layer in hls_config['LayerName'].keys():
    hls_config['LayerName'][Layer]['Precision'] = 'ap_fixed<32,8>'
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

hls_model.build(reset=False, csim=False, synth=False, cosim=False,
                validation=False, export=False, vsynth=False, fifo_opt=False)

# hls_model.compile()
# test_predictions = hls_model.predict(test_images)
# true = 0
# for i in range(10000):
#     # print(i)
#     # print("Labels:", test_labels[i])
#     # print("Predictions:", test_predictions[i])
#     if numpy.argmax(test_predictions[i]) == numpy.argmax(test_labels[i]):
#         true = true + 1
# print(true/10000)
