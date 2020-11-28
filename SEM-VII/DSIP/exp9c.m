clear;
clc;
con = 1;
n = 5;
sig=0.5; 
mid=(n+1)/2;
sum=0; 
p=1-mid; 
for i=1:n 
q=1-mid; 
for j=1:n
t1=(p^2+q^2)/(2*sig^2); 
f(i,j)=exp(-t1); 
sum=sum+f(i,j);
q=q+1; 
end 
p=p+1; 
end
t2=2*pi*sig^6*sum;
p=1-mid;
for i=1:n 
q=1-mid; 
for j=1:n
t1=(p^2+q^2)-(2*sig^2); g(i,j)=(t1*f(i,j))/t2; 
q=q+1;
end 
p=p+1; 
end
g
a = rgb2gray(imread('image.jpg'));
C = conv2(a, h);


subplot(1, 2, 1),
imshow(a),
title('original image');
subplot(1, 2, 2),
imshow(uint8(C)),
title('Laplacian image');
 title('LOG image');
