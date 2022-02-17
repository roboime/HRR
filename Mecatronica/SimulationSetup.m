close all; clc;
addpath("Subsystems\");
addpath("STEP_Files\");
run('Simulador_DataFile.m');

%% Enviorment varialbles
% Ground Variables
startHeight = 0.26;
yGridVector = [-.5 .5];
xGridVector = [0 1.5 1.501 2 2.001 2.5 2.501 3 3.001 3.5 3.501 4 4.001 5] - 0.2;
stepVector = [.015 .015; .015 .015; .015 .015; .015 .015;];
stepType = 1;
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
%% RL stuff
Ts = 25;
mdl = 'Simulador';
obsInfo = rlNumericSpec([28 1]);
actInfo = rlNumericSpec([12 1]);
actInfo.LowerLimit = 0;
actInfo.UpperLimit = 0;
obsInfo.Name = 'observations';
actInfo.Name = 'position';
agentBlk = [mdl '/RL Agent'];
env = rlSimulinkEnv(mdl,agentBlk,obsInfo,actInfo);
agent = rlPGAgent(obsInfo,actInfo);



%% info
%{
the max input frequency is 200Hz
AX max angular velocity is 59 (when charged) (do bentch test to verify)
MX max angular velocity is 55 RPM (when charged) (do bentch test to verify)
Max torc AX12 1.5 Nm
Max torc MX28 2.5 Nm
%}


%sim('Simulador.slx');