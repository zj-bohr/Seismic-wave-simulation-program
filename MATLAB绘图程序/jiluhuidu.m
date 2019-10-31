clear all;
load Seis_Record.dat;
m=Seis_Record(1);
n=Seis_Record(2);
mm=load('Seis_Record.dat');
x=length(mm);
s=reshape(mm([3:x]),n,m);
imagesc(s);
colormap('gray');
