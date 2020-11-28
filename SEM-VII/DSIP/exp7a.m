clear;
clc;
A = imread('image.jpg');
A = im2double(A);
con = 1;
gamma = 1.9
B = con * A .^ gamma;
subplot(1, 2, 1), imshow(A), title('Original Image'); 
subplot(1, 2, 2), imshow(B), title('Image after power law transformation');
