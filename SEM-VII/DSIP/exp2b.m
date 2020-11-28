clc; 
clear all; 
%* generate the sine wave sequence 
fs=8000; 
N=100; 
n=0:N-1;
x=2*sin(2000*pi*[0:1:N-1]/fs);
%**Hamming windowed sequence ** 
w=hamming(N);
xw=x.*w';
%** DFT algorithm *****
 k=0:N-1;
WN=exp(-j*2*pi/N*n'*k); 
Xk=xw*WN;
Xf=abs(Xk)/N;
% Map the frequency bin k to f (Hz)
 f=k*fs/N;
subplot(121); 
plot(f,Xf); 
xlabel('frequency');
title('Spectrum upto sampling frequency');
%** frequencies upto the folding frequency
 f=[0:1:N/2]*fs/N;
subplot(122); 
plot(f,Xf(1:N/2+1)); 
xlabel('frequency');
title('Spectrum upto folding frequency');
