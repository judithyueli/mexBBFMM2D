% call mxFMM2D
Nx =80; Ny = 80; N = Nx*Ny;
x = linspace(0,1,Nx);
y = linspace(0,1,Ny);
[xloc,yloc] = meshgrid(x,y);
% Store location in column-wise fashion
xloc = xloc(:);  yloc = yloc(:);
% The right muliplier H, each column is a Nx1 vector 
H = ones(N,100);
[Q,QHexact,QH] = mexFMM2D(@(x) x.^2, xloc, yloc,H);