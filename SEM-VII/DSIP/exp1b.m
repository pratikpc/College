clc; 
clear all; 
close all; 
for n=0:25;
s=0;
for m=0:10
s=s+(m+1)*(((n-2*m)==0)-((n-2*m+1)==0));
end 
x1(n+1)=s; 
end
n=0:25;
subplot(121); stem(n,x1,'.');
xlabel('n'); ylabel('amplitude'); 
n=-5:5;
x2=2*(n+2==0)+(n==0)-(n-4==0);
subplot(122); 
stem(n,x2,'.'); 
xlabel('n'); 
ylabel('amplitude');
