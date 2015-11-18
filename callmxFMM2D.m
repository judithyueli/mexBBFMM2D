%% Example: Q*H

% Info on dimensions
Nx =100; Ny = 100; N = Nx*Ny;

% Store location (x,y) for each grid in a column-wise fashion
% x and y each is a Nx1 vector
x = linspace(0,1,Nx);
y = linspace(0,1,Ny);
[xloc,yloc] = meshgrid(x,y);
xloc = xloc(:);  yloc = yloc(:);


%% testing mode 
H = ones(N,100);    % right muliplier H, each column is a Nx1 vector
nCheb = 6;          % number of Chebyshev node
print = true;       % print exact computation time and accuracy

% Compute matrix-matrix product QH of dimension 10000x100
[QH,QHexact] = case1(xloc, yloc,H,nCheb,print);

%% application mode
QH = case1(xloc, yloc,H,nCheb,print);
