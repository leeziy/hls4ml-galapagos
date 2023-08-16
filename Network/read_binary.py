import numpy


def cifar10_unbatch(file, feature_output, label_output):
    f = open("cifar-10-batches-bin/" + file, "rb")
    cifar10 = f.read()
    f.close()
    for i in range(10000):
        print(i)
        feature_raw = cifar10[(i*3073+1):(i+1)*3073]
        feature_raw = numpy.frombuffer(feature_raw, dtype=numpy.uint8)
        feature_raw = numpy.float32(feature_raw / 255)
        feature = numpy.zeros((32, 32, 3), dtype=numpy.float32)
        for x in range(32):
            for y in range(32):
                for z in range(3):
                    feature[x][y][z] = feature_raw[z * 1024 + x * 32 + y]
        feature_output.append(feature)

        label = numpy.zeros(10, dtype=numpy.uint8)
        label[cifar10[i*3073]] = 1
        label_output.append(label)