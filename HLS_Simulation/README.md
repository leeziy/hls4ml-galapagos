HLS4ML生成的XX_test.cpp文件中，载入的"tb_input_features.dat"与"tb_output_predictions.dat"文件的格式要求是：
（1）每一个输入帧为一行，行尾使用“\n”作为结束符，中间不能出现该结束符。
（2）一行中，每个数字之间使用空格“ ”作为分隔符。
（3）数据的格式为按像素排列。
（4）标签使用one-hot编码。

输入格式示意：
pixel_1_R pixel_1_G pixel_1_B pixel_2_R pixel_2_G pixel_2_B ...... pixel_N_R pixel_N_G pixel_N_B \n

标签格式示意：
label_0 label_1 label_2 ...... label_9 \n
