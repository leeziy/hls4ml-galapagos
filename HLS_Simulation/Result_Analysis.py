import numpy
import sys
import tensorflow as tf

numpy.set_printoptions(threshold=sys.maxsize, linewidth=sys.maxsize)

f = open(r"E:\SYSU\Project-HLS4ML\Python\cifar-10-batches-bin\test_batch.bin", "rb")
cifar10 = f.read()
f.close()

f = open(r"csim_results.log", "r")
log = f.readlines()
f.close()

true = 0
i = 0
for item in log:
    prediction = item.split(sep=" ")
    prediction = numpy.float32(prediction[0:10])
    result = numpy.argmax(prediction)
    if result == cifar10[i*3073]:
        true = true + 1
    i = i + 1
print(true/i)
