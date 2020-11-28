clear;
clc;
B = imread ('image.jpg');
B = uint8(B);
B = rgb2gray(B);
imhist(B);