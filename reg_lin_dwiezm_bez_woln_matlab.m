%Regresja liniowa dwoch zmiennych bez wyrazu wolnego

N = 30;

dane = 'dane2.txt';%punkty sa obierane z pliku
XYZ = importdata(dane);

X = 0;
Y1 = 0;
Y2 = 0;


for i=1:N
    
   X = [X, XYZ(1, i)];
        
   Y1 = [Y1, XYZ(2, i)];  
   
   Y2 = [Y2, XYZ(3, i)]; 

end

Y1 = Y1(2:end);
X = X(2:end);
Y2 = Y2(2:end);

sumailoczxy1=0;
for i=1:N
    sumailoczxy1 = sumailoczxy1 + X(i)*Y1(i);   
end
sumailoczxy2=0;
for i=1:N
    sumailoczxy2 = sumailoczxy2 + X(i)*Y2(i);   
end
sumailoczy1y2=0;
for i=1:N
    sumailoczy1y2 = sumailoczy1y2 + Y1(i)*Y2(i);   
end
sumax=0;
for i=1:N
    sumax = sumax + X(i);   
end
sumay1=0;
for i=1:N
    sumay1 = sumay1 + Y1(i);   
end
sumay2=0;
for i=1:N
    sumay2 = sumay2 + Y2(i);   
end
sumay12=0;
for i=1:N
    sumay12 = sumay12 + Y1(i)*Y1(i);   
end
sumax2=0;
for i=1:N
    sumax2 = sumax2 + X(i)*X(i);   
end
sumajed=0;
for i=1:N
    sumajed = sumajed + 1;   
end

T1j = [sumax2, sumailoczxy1; sumailoczxy1, sumay12];

T2j = [sumailoczxy2; sumailoczy1y2];

Aj = (T1j^(-1))*T2j,

plot3(X, Y1, Y2, 'bo'); hold on;



xp = 0:N;

yp = 0:N;

syms fj(x, y);

fj(x, y) = Aj(1) * x + Aj(2) * y;

plot3(xp, yp, fj(xp, yp)); hold on;
