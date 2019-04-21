%funkcja uzywana w projekcie sieci neuronowych
function l = wynik(Y)
%Y <- wyjscie neuronu
%pokazuje ktora litera zostala rozpoznana

[M, I] = max(Y);
for i = 1:23

    switch I(i)
        case 1
            disp('A')
        case 2
            disp('B')
        case 3
            disp('C')
        case 4
            disp('D')
        case 5
            disp('E')
        case 6
            disp('F')
        case 7
            disp('G')
        case 8
            disp('H')
        case 9
            disp('I')
        case 10
            disp('J')
        case 11
            disp('K')
        case 12
            disp('L')
        case 13
            disp('M')
        case 14
            disp('N')
        case 15
            disp('O')
        case 16
            disp('P')
        case 17
            disp('R')
        case 18
            disp('R')
        case 19
            disp('T')
        case 20
            disp('U')
        case 21
            disp('W')
        case 22
            disp('Y')
        case 23
            disp('Z')
      
        otherwise
            disp('other value')
    end
end

    l = I;

end