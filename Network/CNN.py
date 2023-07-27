import tensorflow as tf
from keras import datasets, models, layers, losses, optimizers, callbacks, Model
import matplotlib.pyplot as plt
import numpy

(train_images, train_labels), (test_images, test_labels) = datasets.cifar10.load_data()
train_images, test_images = train_images / 255.0, test_images / 255.0

inputs = layers.Input(shape=(32, 32, 3))
network = layers.Conv2D(64, kernel_size=3, strides=1, padding="same")(inputs)
network = layers.ReLU()(network)
network = layers.MaxPooling2D(pool_size=(2, 2))(network)
network = layers.Conv2D(64, kernel_size=3, strides=1, padding="same")(network)
network = layers.ReLU()(network)
network = layers.MaxPooling2D(pool_size=(2, 2))(network)
network = layers.Conv2D(64, kernel_size=3, strides=1, padding="same")(network)
network = layers.ReLU()(network)
network = layers.MaxPooling2D(pool_size=(2, 2))(network)
network = layers.Conv2D(64, kernel_size=3, strides=1, padding="same")(network)
network = layers.ReLU()(network)
network = layers.Flatten()(network)
network = layers.Dense(128)(network)
network = layers.ReLU()(network)
network = layers.Dense(10)(network)
outputs = layers.Softmax()(network)

model = Model(inputs, outputs)
model.summary()

model.compile(optimizer=optimizers.Adam(learning_rate=0.0003),
              loss=losses.SparseCategoricalCrossentropy(),
              metrics=['accuracy'])

history = model.fit(train_images, train_labels, epochs=500, batch_size=500,
                    validation_data=(test_images, test_labels), validation_batch_size=500,
                    callbacks=[callbacks.EarlyStopping(monitor='val_accuracy', patience=100,
                                                       mode='max', verbose=1, restore_best_weights=True)])


plt.plot(history.history['accuracy'], label='accuracy')
plt.plot(history.history['val_accuracy'], label='val_accuracy')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.ylim([0.5, 1])
plt.legend(loc='lower right')
plt.show()

model.save("CNN.h5")
