% This is an example file with the input for using mexBBFMM2D to multiply the covariance matrix
% for a regular 100 x 100 grid, with matrix H. 
% -----------
%Type "help runmexBFMM2D" for more information on the input variables in this file 

ExecName = 'case1_test';
TestingMode = true; 

% Modify xloc and yloc for your own example

Nx =100; Ny = 100; N = Nx*Ny;
x = linspace(0,1,Nx);
y = linspace(0,1,Ny);
[xloc,yloc] = meshgrid(x,y);
xloc = xloc(:);  yloc = yloc(:);

% Modify H, nCheb and PrintFlag for your own example

H = ones(N,100);    % right muliplier H, each column is a Nx1 vector
nCheb = 3;          % number of Chebyshev node
PrintFlag = true;   % print exact computation time and accuracy

% run mexBBFMM2D

QH = runmexBBFMM2D(xloc, yloc,H,nCheb,PrintFlag,ExecName,TestingMode);

