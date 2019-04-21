%Program losuje liczby z dowolnego rozkladu prawdobodobienstwa okreslonego
%funkcja 
%Metoda Rejection Sampling
clc; clear; close all;

a = 9/7;
fun = @(x)(sin(x)+1)/6; %funkcja okreslajaca rozklad prawdopodobienstwa
a = 0;
b = 10;

db = 0.1; %dok³adnoœæ normalizacji

%normalizacja funkcji-------------------
while (integral(fun, a, b) - 1) > db
    
    if integral(fun, a, b) > 1        
        b = b - db;        
    end
    
    if integral(fun, a, b) < 1        
        b = b + db;        
    end    
end
%-----------------------------------------

xt = a:0.1:b; hold on;
plot(xt, fun(xt));
integral(fun, a, b),

dx = 0.5; %szerokoœæ binów
N = ceil((b - a)/dx);
X = 0;
iletrafilo = 10000;

while iletrafilo > 0    
    xrand = rand * b;
    yrand = rand;
    
    if fun(xrand) >= yrand        
        X = [X, xrand];        
        iletrafilo = iletrafilo - 1;
    end
end
%ile binów ----------------------------------------------------------
%Rysowanie histogramu
ilebin = 20;

h = histogram(X, ilebin,'Normalization','pdf');




