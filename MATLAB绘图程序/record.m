clear all;
load Seis_Record.dat;
m=Seis_Record(1);
n=Seis_Record(2);
len=length(Seis_Record)-2;
nn=len/m;
if n~=nn; disp('The data file length error!'); return; end
 
dx=1;
dz=1;
for i=1:m
    for j=1:n
        x(j)=(i-1)*dx+Seis_Record((i-1)*n+j+2)*0.5*dx;
        y(j)=(j-1)*dz;
    end
    plot(x,y,'k');
    hold on
end
axis ij;
title('Seis_Record of theretical wavefield');    
