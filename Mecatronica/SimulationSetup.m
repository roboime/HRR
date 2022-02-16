close all; clc;

%% Enviorment varialbles
% Ground Variables
yGridVector = [0 1];
xGridVector = [0 1.5 1.501 2 2.001 2.5 2.501 3 3.001 3.5 3.501 4 4.001 5];
stepVector = [.015 .015; .015 .015; .015 .015; .015 .015;];
stepType = 0;
switch stepType
    case 1
        zHeigths = [0 0; 0 0; stepVector; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0;];
    case 2
        zHeigths = [0 0; 0 0; 0 0; 0 0; stepVector; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0;];
    case 3
        zHeigths = [0 0; 0 0; 0 0; 0 0; 0 0; 0 0; stepVector; 0 0; 0 0; 0 0; 0 0;];
    case 4
        zHeigths = [0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; stepVector; 0 0; 0 0;];
    otherwise
        zHeigths = [0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0; 0 0;];
end

