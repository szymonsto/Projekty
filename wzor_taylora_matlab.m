function f=wzor_taylora(fun, a, N)
%f=wzor_taylora(fun, a, N)
%przybi¿a funkcjê wzorem Taylora
%fun -> funkcja, któr¹ trzeba przybli¿yæ
%a -> punkt pocz¹tkowy
%N -> liczba wyrazów we wzorze Taylora
%

x1=a - 5;  %pocz¹tek i koniec wykresu
x2=a + 5;

fun = str2sym(fun);

X=x1:0.01:x2;  %potrzebane do rysowania

syms f(x);
syms taylor(x);

f(x) = fun;

ymax = max(f(X));   %potrzebne do ustalania wartoœci na osi wykresów
ymin = min(f(X));

ymin=double(ymin);
ymax=double(ymax);

subplot(2, 1, 1);   %rysuje prawdziw¹ funkcjê 
plot(X, f(X), 'b-'); hold on;
axis([x1 x2 ymin ymax]);


taylor(x)=f(a); %pierwszy wyraz we wzorze Taylora


syms poch(x);    %bêdzie przechowywaæ wartoœæ pochodnej w punkcie   

N=N-1;

for n=1:N   %w tej pêtli bêd¹ dopisywane kolejne wyrazy do wzoru Taylora    
    poch(x) = diff(f, n);
    taylor(x)=taylor(x) + (((x - a)^n)* poch(a))/factorial(n);  %wzór Taylora    
    subplot(2, 1, 2);       %rysuje kolejne kroki
    plot(X, taylor(X)); hold on;
    axis([x1 x2 ymin ymax]);
    pause(1);
end

 subplot(2, 1, 1);  %nanosi koñcowy wzór Taylora na wykres z prawdziw¹ funkcj¹
 plot(X, taylor(X), 'r--'); hold on;
 axis([x1 x2 ymin ymax]);
 
 fun=taylor(x); 
end