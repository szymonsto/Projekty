%funkcja uzywana w projekcie sieci neuronowych
function W = wagipocz(ilewejsc, ileneuronow)
    W = ((rand(ilewejsc, ileneuronow).*2)-1)/10;    
end