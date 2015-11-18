%% Example: Q*H

% Info on dimensions
Nx =100; Ny = 100; N = Nx*Ny;

% Store location (x,y) for each grid in a column-wise fashion
% x and y each is a Nx1 vector
x = linspace(0,1,Nx);
y = linspace(0,1,Ny);
[xloc,yloc] = meshgrid(x,y);
xloc = xloc(:);  yloc = yloc(:);


% The right muliplier H, each column is a Nx1 vector 
H = ones(N,100); nCheb = 6;
print = true;
% Clear memory associated with output
% clear QH QHexact

% Compute matrix-matrix product QH of dimension 10000x100
[QH,QHexact] = case1(xloc, yloc,H,nCheb,print);

