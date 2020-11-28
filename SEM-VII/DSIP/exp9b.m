clear;
clc;
r = size(a, 1);
c = size(a, 2);
si = 3;
alp = 0.7;
m = (si / 2) + 0.5;
h1 = alp / (alp + 1);
h2 = (1 - alp) / (alp + 1);
h3 = -4 / (alp + 1);
h = [h1 h2 h1; h2 h3 h2; h1 h2 h1];
display(h);

a = rgb2gray(imread('image.jpg'));
C = conv2(a, h);


subplot(1, 2, 1),
imshow(a),
title('original image');
subplot(1, 2, 2),
imshow(uint8(C)),
title('Laplacian image');
