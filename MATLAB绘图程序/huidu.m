clear all;
load wavefront.dat;
m=wavefront(1);
n=wavefront(2);
mm=load('wavefront.dat');
x=length(mm);
s=reshape(mm([3:x]),n,m);
imagesc(s);
colormap('gray');
