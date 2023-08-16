import numpy
import sys
import tensorflow as tf

numpy.set_printoptions(threshold=sys.maxsize, linewidth=sys.maxsize)

f = open(r"E:\SYSU\Project-HLS4ML\Python\cifar-10-batches-bin\test_batch.bin", "rb")
cifar10 = f.read()
f.close()

tb_input_features = open("tb_input_features.dat", "a")
tb_output_predictions = open("tb_output_predictions.dat", "a")

for i in range(500):
    print(i)

    feature_raw = cifar10[(i*3073+1):(i+1)*3073]
    feature_raw = numpy.frombuffer(feature_raw, dtype=numpy.uint8)
    feature_raw = numpy.float32(feature_raw / 255)
    feature = numpy.zeros(3072, dtype=numpy.float32)
    for j in range(1024):
        feature[j * 3] = feature_raw[j]
        feature[j * 3 + 1] = feature_raw[j+1024]
        feature[j * 3 + 2] = feature_raw[j+2048]
    feature = numpy.array2string(feature)
    feature = feature.strip("[]")
    feature = feature + " \n"

    label = numpy.zeros(10, dtype=numpy.uint8)
    label[cifar10[i*3073]] = 1
    label = numpy.array2string(label)
    label = label.strip("[]")
    label = label + " \n"

    tb_input_features.write(feature)
    tb_output_predictions.write(label)

tb_input_features.close()
tb_output_predictions.close()
