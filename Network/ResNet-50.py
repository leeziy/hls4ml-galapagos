import tensorflow as tf
from keras import datasets, models, layers, losses, optimizers, callbacks, applications, Model
import matplotlib.pyplot as plt
import numpy

(train_images, train_labels), (test_images, test_labels) = datasets.cifar10.load_data()
train_images, test_images = train_images / 255.0, test_images / 255.0

RESNET_input = layers.Input(shape=(32, 32, 3))
RESNET = applications.ResNet50(
    include_top=False,
    weights="imagenet",
    input_tensor=RESNET_input,
    pooling=None)

for layer in RESNET.layers:
    layer.trainable = True

RESNET_layer = RESNET.output
# RESNET_layer = layers.Flatten()(RESNET_layer)
RESNET_layer = layers.Dense(64, activation='relu')(RESNET_layer)
RESNET_layer = layers.ReLU()(RESNET_layer)
RESNET_result = layers.Dense(1, activation='sigmoid')(RESNET_layer)

RESNET_model = Model(RESNET_input, RESNET_result)
RESNET_model.summary()
