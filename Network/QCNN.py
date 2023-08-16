from keras import datasets, models, layers, losses, optimizers
import qkeras
import matplotlib.pyplot as plt
import numpy

(train_images, train_labels), (test_images, test_labels) = datasets.cifar10.load_data()

# Normalize pixel values to be between 0 and 1
train_images, test_images = train_images / 255.0, test_images / 255.0

model = models.Sequential()
model.add(qkeras.QConv2D(64, (3, 3), activation=qkeras.quantized_relu(16, 6),
                         kernel_quantizer=qkeras.quantized_bits(16, 6, 1),
                         bias_quantizer=qkeras.quantized_bits(16, 6, 1),
                         input_shape=(32, 32, 3)))
model.add(layers.MaxPooling2D((2, 2)))
model.add(qkeras.QConv2D(64, (3, 3), activation=qkeras.quantized_relu(16, 6),
                         kernel_quantizer=qkeras.quantized_bits(16, 6, 1),
                         bias_quantizer=qkeras.quantized_bits(16, 6, 1)))
model.add(layers.MaxPooling2D((2, 2)))
model.add(qkeras.QConv2D(64, (3, 3), activation=qkeras.quantized_relu(16, 6),
                         kernel_quantizer=qkeras.quantized_bits(16, 6, 1),
                         bias_quantizer=qkeras.quantized_bits(16, 6, 1)))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Flatten())
model.add(qkeras.QDense(64, activation=qkeras.quantized_relu(16, 6),
                        kernel_quantizer=qkeras.quantized_bits(16, 6, 1),
                        bias_quantizer=qkeras.quantized_bits(16, 6, 1)))
model.add(qkeras.QDense(10,
                        kernel_quantizer=qkeras.quantized_bits(16, 6, 1),
                        bias_quantizer=qkeras.quantized_bits(16, 6, 1)))

model.summary()

for layer in model.layers:
    if layer.__class__.__name__ in ['Conv2D', 'Dense']:
        w = layer.get_weights()[0]
        layersize = numpy.prod(w.shape)
        print("{}: {}".format(layer.name, layersize))  # 0 = weights, 1 = biases
        if layersize > 4096:  # assuming that shape[0] is batch, i.e., 'None'
            print("Layer {} is too large ({}), are you sure you want to train?".format(layer.name, layersize))

model.compile(optimizer=optimizers.Adam(learning_rate=0.0003),
              loss=losses.SparseCategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])

history = model.fit(train_images, train_labels, epochs=100, batch_size=50,
                    validation_data=(test_images, test_labels), validation_batch_size=50)

plt.plot(history.history['accuracy'], label='accuracy')
plt.plot(history.history['val_accuracy'], label='val_accuracy')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.ylim([0.5, 1])
plt.legend(loc='lower right')
plt.show()

model.save("QCNN.keras")
