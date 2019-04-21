function Wynik=montecarlo3d(N)
%Wynik=montecarlo3d(N)
%Obilcza ca�k� funckcji dwoch zmiennych metoda Monte Carlo
a = 0;%poczatek przedzia�u
b = 2;%koniec przedzia�u
[X,Y] = meshgrid(a:.2:b);                                
Z =@(X, Y) X .* exp(-X.^2 - Y.^2);

iletrafilo = N; %przechouje N, bo w p�tli N jest zerowane, a p�niej b�dzie potrzebne do obliczenia wyniku
ilewszystkich = 0;%liczba wszyskich losowa�

while N > 0    
    xrand = rand * b;
    yrand = rand * b;
    zrand = rand * b;
    
    if Z(xrand, yrand) >= zrand        
        N = N - 1;    
    end
       
    ilewszystkich = ilewszystkich + 1;    
end

wynik = b^3 * (iletrafilo/ilewszystkich);
Wynik = wynik;
end