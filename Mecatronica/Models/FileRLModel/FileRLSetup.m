clear; close all; clc;
addpath("Subsystems\");
addpath("STEP_Files\");
run('SimulatorDataFile.m');

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

%% Simulation Setup
% Specify the simulation time Tf and the agent sample time Ts in seconds.
Ts = 1.0;
Tf = 200;
% Fix the random generator seed for reproducibility.
rng(0);

%% RL Enviorment Setup
mdl = 'Simulator';
numObservations = 33;
numActions = 12;
%open_system(mdl)
obsInfo = rlNumericSpec([numObservations 1]);
obsInfo.Name = 'Observarion';
actInfo = rlNumericSpec([numActions 1], LowerLimit = -pi, UpperLimit = pi);
actInfo.Name = 'Action';
agentBlk = [mdl '/RL Agent'];
env = rlSimulinkEnv(mdl,agentBlk,obsInfo,actInfo);
% env.ResetFcn = @(in)localResetFcn(in);

%% RL Agent Setup
% Critic
useGPU = true;
statePath = [
    featureInputLayer(numObservations,'Normalization','none','Name','State')
    fullyConnectedLayer(400,'Name','CriticStateFC1')
    reluLayer('Name','CriticRelu1')
    fullyConnectedLayer(300,'Name','CriticStateFC2')];
actionPath = [
    featureInputLayer(numActions,'Normalization','none','Name','Action')
    fullyConnectedLayer(300,'Name','CriticActionFC1')];
commonPath = [
    additionLayer(2,'Name','add')
    reluLayer('Name','CriticCommonRelu')
    fullyConnectedLayer(1,'Name','CriticOutput')];

criticNetwork = layerGraph();
criticNetwork = addLayers(criticNetwork,statePath);
criticNetwork = addLayers(criticNetwork,actionPath);
criticNetwork = addLayers(criticNetwork,commonPath);
criticNetwork = connectLayers(criticNetwork,'CriticStateFC2','add/in1');
criticNetwork = connectLayers(criticNetwork,'CriticActionFC1','add/in2');


%figure
%plot(criticNetwork)

criticOpts = rlRepresentationOptions('LearnRate',1e-03,'GradientThreshold',1);

if useGPU
   criticOpts.UseDevice = 'gpu'; 
end

critic = rlQValueRepresentation(criticNetwork,obsInfo,actInfo,'Observation',{'State'},'Action',{'Action'},criticOpts);  

% Actor

actorNetwork = [
    featureInputLayer(numObservations,'Normalization','none','Name','State')
    fullyConnectedLayer(400, 'Name','ActorFC1')
    reluLayer('Name','ActorRelu1')
    fullyConnectedLayer(400, 'Name','ActorFC2')
    reluLayer('Name','actorTanh')
    fullyConnectedLayer(numActions,'Name','ActionFC3')
    tanhLayer('Name','ActorTanh1')
    ];

actorOptions = rlRepresentationOptions('LearnRate',1e-04,'GradientThreshold',1);

if useGPU
   actorOptions.UseDevice = 'gpu'; 
end

actor = rlDeterministicActorRepresentation(actorNetwork,obsInfo,actInfo,'Observation',{'State'},'Action',{'ActorTanh1'},actorOptions);

agentOpts = rlDDPGAgentOptions(...
    'SampleTime',Ts,...
    'TargetSmoothFactor',1e-3,...
    'DiscountFactor',1.0, ...
    'MiniBatchSize',64, ...
    'ExperienceBufferLength',1e6); 
agentOpts.NoiseOptions.Variance = 0.3;
agentOpts.NoiseOptions.VarianceDecayRate = 1e-5;

agent = rlDDPGAgent(actor,critic,agentOpts);

%% Train Agents
maxepisodes = 5000;
maxsteps = ceil(Tf/Ts);
trainOpts = rlTrainingOptions(...
    'MaxEpisodes',maxepisodes, ...
    'MaxStepsPerEpisode',maxsteps, ...
    'ScoreAveragingWindowLength',20, ...
    'Verbose',false, ...
    'Plots','training-progress',...
    'StopTrainingCriteria','AverageReward',...
    'StopTrainingValue',800);

doTraining = true;

if doTraining
    % Train the agent.
    trainingStats = train(agent,env,trainOpts);
else
    % Load the pretrained agent for the example.
    load('WaterTankDDPG.mat','agent')
end



