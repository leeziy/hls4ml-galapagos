import numpy
import sys
import tensorflow as tf

numpy.set_printoptions(threshold=sys.maxsize, linewidth=sys.maxsize)
# print(sys.maxsize)

(train_images, train_labels), (test_images, test_labels) = tf.keras.datasets.cifar10.load_data()
train_images, test_images = train_images / 255.0, test_images / 255.0

# f = open(r"E:\SYSU\Project-HLS4ML\Python\cifar-10-batches-bin\data_batch_1.bin", "rb")
# cifar10 = f.read()
# f.close()

tb_input_features = open("tb_input_features.dat", "a")
tb_output_predictions = open("tb_output_predictions.dat", "a")

for i in range(10000):
    print(i)

    feature_raw = train_images[i]
    feature_raw = numpy.reshape(feature_raw, [1024, 3])
    feature = numpy.zeros(3072, dtype=numpy.float32)
    for j in range(1024):
        feature[j * 3] = feature_raw[j][0]
        feature[j * 3 + 1] = feature_raw[j][1]
        feature[j * 3 + 2] = feature_raw[j][2]
    # print(feature)
    # feature = numpy.float32(feature / 255)
    feature = numpy.array2string(feature)
    feature = feature.strip("[]")
    feature = feature + " \n"

    label = numpy.zeros(10, dtype=numpy.uint8)
    label[train_labels[i]] = 1
    label = numpy.array2string(label)
    label = label.strip("[]")
    label = label + " \n"

    tb_input_features.write(feature)
    tb_output_predictions.write(label)

tb_input_features.close()
tb_output_predictions.close()
