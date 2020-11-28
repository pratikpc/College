% simple implementation of frequency domain filters clear all
%read input image 
dim=imread('sid.png'); 
cim=double(dim); 
[r,c]=size(cim);

r1=2*r; 
c1=2*c;

%%aFunction for Gaussian Low Pass Filter
function res = glp(im,thresh)

% inputs
% im is the fourier transform of the image
% thresh is the cutoff circle radius
%outputs
% res is the filtered image

[r,c]=size(im); 
d0=thresh; 
d=zeros(r,c);
h=zeros(r,c);

for i=1:r 
for j=1:c
d(i,j)= sqrt( (i-(r/2))^2 + (j-(c/2))^2); 
end
end

for i=1:r 
for j=1:c
h(i,j)=1- exp ( -( (d(i,j)^2)/(2*(d0^2)) ) ); 
end
end


for i=1:r 
for j=1:c
res(i,j)=(h(i,j))*im(i,j); 
end
end
endfunction
%%aFunction for Butterworth Low Pass Filter
function res = blpf(im,thresh,n)

% inputs
% im is the fourier transform of the image
% thresh is the cutoff circle radius (1,2,3...)
% n is the order of the filter (1,2,3...)

%outputs
% res is the filtered image

[r,c]=size(im); 
d0=thresh; d=zeros(r,c);
h=zeros(r,c);

for i=1:r 
for j=1:c
d(i,j)= sqrt( (i-(r/2))^2 + (j-(c/2))^2); 
end
end

for i=1:r 
for j=1:c
h(i,j)= 1 / (1+ (d(i,j)/d0)^(2*n) ) ; 
end
end


for i=1:r 
for j=1:c
res(i,j)=(h(i,j))*im(i,j); 
end
end
endfunction
%%aFunction for Gaussian High Pass Filter
function res = ghp(im,thresh)

% inputs
% im is the fourier transform of the image
% thresh is the cutoff circle radius

%outputs
% res is the filtered image

[r,c]=size(im); 
d0=thresh; d=zeros(r,c);
h=zeros(r,c);
for i=1:r 
for j=1:c
d(i,j)= sqrt( (i-(r/2))^2 + (j-(c/2))^2); 
end
end

for i=1:r 
for j=1:c
h(i,j)=1- exp ( -( (d(i,j)^2)/(2*(d0^2)) ) ); 
end
end


for i=1:r 
for j=1:c
res(i,j)=(h(i,j))*im(i,j); 
end
end
endfunction
%%a Function for High boost filtering (Butterworth High pass filter)
function res =hbb(im,thresh,n)

% Butterworth High passfilter
% inputs
% im is the fourier transform of the image
% thresh is the cutoff circle radius
%outputs
% res is the filtered image

[r,c]=size(im); 
d0=thresh;

d=zeros(r,c);
h=zeros(r,c);
A=1.75; % boost factor or coefficient

for i=1:r 
for j=1:c
d(i,j)= sqrt( (i-(r/2))^2 + (j-(c/2))^2); 
end
end

for i=1:r 
for j=1:c
h(i,j)= 1 / (1+ (d0/d(i,j))^(2*n) ) ;
h(i,j)=(A-1)+h(i,j); 
end
end


for i=1:r 
for j=1:c
res(i,j)=(h(i,j))*im(i,j); 
end
end

endfunction
%%a Function for High boost filtering (Gaussian High pass filter)
function res = hbg(im,thresh)

% inputs
% im is the fourier transform of the image
% thresh is the cutoff circle radius
%outputs
% res is the boosted image

[r,c]=size(im); 
d0=thresh; 
d=zeros(r,c);
h=zeros(r,c);

for i=1:r 
for j=1:c
d(i,j)= sqrt( (i-(r/2))^2 + (j-(c/2))^2); 
end
end
A=1.75; % boost factor or coefficient 
for i=1:r
for j=1:c
h(i,j)= 1-exp ( -( (d(i,j)^2)/(2*(d0^2)) ) ); 
h(i,j)=(A-1)+h(i,j);
end 
end

for i=1:r 
for j=1:c
res(i,j)=(h(i,j))*im(i,j); 
end
end
endfunction

pim=zeros((r1),(c1));
kim=zeros((r1),(c1));

%padding 
for i=1:r
for j=1:c 
pim(i,j)=cim(i,j); 
end
end

%center the transform

for i=1:r 
for j=1:c
kim(i,j)=pim(i,j)*((-1)^(i+j)); 
end
end
subplot(2,3,2);imshow(uint8(kim));title('Padding');


%2D fft
 fim=fft2(kim);
 subplot(2,3,3);imshow(uint8(real(fim)));title('Transform centering');

n=1; 
%order for butterworth filter
thresh=10; 
% cutoff radius in frequency domain for filters

% % function call for low pass filters
 him=glp(fim,thresh); 
 subplot(2,3,4);imshow(uint8(real(him)));title('Fourier Transform');
% gaussian low pass filter
 him=blpf(fim,thresh,n); 
 subplot(2,3,4);imshow(uint8(real(him)));title('Fourier Transform');
% butterworth low pass filter

% % function calls for high pass filters
 him=ghp(fim,thresh); 
 subplot(2,3,4);imshow(uint8(real(him)));title('Fourier Transform');
% gaussian low pass filter


% % function call for high boost filtering
 him=hbg(fim,thresh); 
 subplot(2,3,4);imshow(uint8(real(him)));title('Fourier Transform');
% using gaussian high pass filter
 him=hbb(fim,thresh,n); 
% using butterworth high pass filter
 subplot(2,3,4);imshow(uint8(real(him)));title('Fourier Transform');


%inverse 2D fft
 ifim=ifft2(him);

for i=1:r1 
for j=1:c1
ifim(i,j)=ifim(i,j)*((-1)^(i+j)); 
end
end
 subplot(2,3,5);imshow(uint8(real(him)));title('Inverse fourier transform');


% removing the padding 
for i=1:r
for j=1:c 
rim(i,j)=ifim(i,j); 
end
end

% retaining the ral parts of the matrix
rim=real(rim);
rim=uint8(rim);

 subplot(2,3,6);imshow(uint8(rim));title('Cropped image');

% figure;
 subplot(2,3,1);imshow(dim);title('Originalimage');
