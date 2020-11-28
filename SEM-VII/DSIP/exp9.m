clear;
clc;
con = 1;

n = 5
mid = (n + 1) / 2;
% for low pass filter.......
for i = 1:n

    for j = 1:n
        lpfmask(i, j) = 1 / (n * n);
    end

end

lpfmask
% for high pass filter
for i = 1:n

    for j = 1:n

        if (i == mid && j == mid)
            hpfmask(i, j) = (-((n * n) - 1) / (n * n));
        else
            hpfmask(i, j) = 1 / (n * n);
        end

    end

end

hpfmask
b = rgb2gray(imread('image.jpg'));
lpfnewimg = conv2(b, lpfmask);
hpfnewimg = conv2(b, hpfmask);
subplot(2, 2, 1); imshow(uint8(b)); title('Original image'); subplot(2, 2, 2); imshow(uint8(lpfnewimg)); title('LPF image'); subplot(2, 2, 3); imshow(uint8(hpfnewimg)); title('HPF image'); 