%This m file is used to load wave data calculated by infinite difference
%method and plot the wave form.
clear all;
load wavefront.dat;
m=wavefront(1);
n=wavefront(2);
len=length(wavefront)-2;
nn=len/m;
if n~=nn; disp('The data file length error!'); return; end

dx=1;
dz=1;
for i=1:m
    for j=1:n
        x(j)=(i-1)*dx+wavefront((i-1)*n+j+2)*0.5*dx;
        y(j)=(j-1)*dz;
    end
    plot(x,y,'k');
    hold on
end
axis ij;
title('Wavefront of theretical wavefield');    
 