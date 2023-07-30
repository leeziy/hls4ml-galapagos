import numpy
import sys
import tensorflow as tf

numpy.set_printoptions(threshold=sys.maxsize, linewidth=sys.maxsize)
# print(sys.maxsize)

(train_images, train_labels), (test_images, test_labels) = tf.keras.datasets.cifar10.load_data()
train_images, test_images = train_images / 255.0, test_images / 255.0

f = open(r"csim_results.log", "r")
log = f.readlines()
f.close()

false = 0
i = 0
for item in log:
    prediction = item.split(sep=" ")
    prediction = numpy.float32(prediction[0:10])
    result = numpy.argmax(prediction)
    if result != train_labels[i]:
        false = false + 1
    i = i + 1
print(false)

