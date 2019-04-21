function [Xwynik, Ywynik] = metoda_gradientu(rown, xp1, yp1);
%[X, Y]metoda_gradientu(rown, xp1, yp1)
%metaoda gradientu prostego dla funkcji dwoch zmiennych
%Zwraca droge do minimum funkcji dwoch zmiennych w zaleznosci od podanego
%punktu poczatkowego
%X -> wektor kolejnych przejœæ do minimum
%Y -> wektor kolejnych przejœæ punktu do minimum
%xp1, yp1 -> punkty pocz¹tkowe
%rown -> równanie
%

%clc; clear; close all;

syms Z(x, y);
Z(x,y) = str2func(rown);
krokzmian=0.5;

%punkty pocz¹tkowe
x1=xp1;
y1=yp1;

Xwynik(1) = x1;
Ywynik(1) = y1;

xval=x1;
yval=y1;

xvalprev=0; %wartoœæ xval w poprzednim wykonaniu pêtli
yvalprev=0;

n=2;

while abs(xval - xvalprev)>0.01 && abs(yval - yvalprev)>0.01
    
    xvalprev = xval;
    yvalprev = yval;
    
    ax=diff(Z, x);

    tempx = ax(x1, y1);

    ay=diff(Z, y);

    tempy = ay(x1, y1);

    x1 = x1 - tempx*krokzmian; 
    y1 = y1 - tempy*krokzmian;
    
    xval = double(x1);
    yval = double(y1);
    
    Xwynik = [Xwynik, xval];
    Ywynik = [Ywynik, yval];

    n = n + 1;
end

Xwynik, Ywynik,

end

