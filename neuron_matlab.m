%funkcja uzywana w projekcie sieci neuronowych
function Y = neuron(wagi, wejscie)
    Y = sigmoid((wagi')*wejscie);
end