%funkcja uzywana w projekcie sieci neuronowych
function Wagipo = uczenie(wagiprzed, wejscia, wyjscia, ileepok)
%Wagipo = uczenie(wagiprzed, wejscia, wyjscia, ileepok)
%Zwraca wagi dla kolejnych elementow obrazu znaku

    ileprzykladow = 23;
    learningrate = 0.1;    
    W = wagiprzed;
    
    for i = 1:ileepok        
        aktualnyprzyklad = ceil(rand(1)*ileprzykladow);        
        X = wejscia(:, aktualnyprzyklad);        
        Y = neuron(W, X);        
        Blad = wyjscia(:, aktualnyprzyklad) - Y;        
        poprawka = learningrate * X * (Blad');        
        W = W + poprawka;        
    end
    Wagipo = W;

end