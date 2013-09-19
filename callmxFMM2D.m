%% Compile mex code for new kernel
syms r;                         % seperation between two points
kernel = exp(-sqrt(r^0.5)/30);  % user input here, kernel has to be a symbolic function
make(r,kernel);
%% Run Example of Q*H
clear all                       % QH and QHexact must be freed before start
% Info on dimensions
Nx =80; Ny = 80; N = Nx*Ny;
% Store location (x,y) for each grid in a column-wise fashion
% x and y each is a Nx1 vector
x = linspace(0,1,Nx);
y = linspace(0,1,Ny);
[xloc,yloc] = meshgrid(x,y);
xloc = xloc(:);  yloc = yloc(:);
% The right muliplier H, each column is a Nx1 vector 
H = ones(N,100); nCheb = 6;
[QH,QHexact] = mexFMM2D(xloc, yloc,H,nCheb);
