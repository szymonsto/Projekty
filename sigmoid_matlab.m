%funkcja uzywana w projekcie sieci neuronowych
function y = sigmoid(x)    
    y = 1./(1+exp(-x));
end