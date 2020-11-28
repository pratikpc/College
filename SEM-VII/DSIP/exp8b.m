clear;
clc;
B = imread ('image.jpg');
B = uint8(B);
B = rgb2gray(B);
equalized = histeq(B);

subplot(2, 2, 1), imshow(B), title('Original Image'); 
subplot(2,2, 2), imshow(equalized), title('Image after equalized histogram');
subplot(2, 2, 3), imhist(equalized), title('Histogram'); 

