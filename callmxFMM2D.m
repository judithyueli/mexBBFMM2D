% call mxFMM2D
Nx =20; Ny = 30; N = Nx*Ny;
x = linspace(0,1,Nx);
y = linspace(0,1,Ny);
[xloc yloc] = meshgrid(x,y);
% Store location in column-wise fashion
xloc = xloc(:);  yloc = yloc(:);
% The right muliplier H, each column is a Nx1 vector 
H = eye(N,N);
[Q,QH] = gatewayfunction(@(x) x.^2, xloc, yloc,H);