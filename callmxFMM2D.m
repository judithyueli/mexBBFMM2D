function QH = callmxFMM2D(ExecFile,TestingMode)

%% This is an example for using mexBBFMM2D to multiply the covariance matrix for a regular 100 x 100 grid, with matrix H. 

%Input:  Outputname as set in the compilemex.m
%        TestingMode: 1 for testing 0 for application
%Output: product QH


% Grid information - regular 100x100 grid in [0,1]
% xloc, yloc: These are the coordinates of each grid point provided as vectors. 
%             These are m x 1 vectors arranged in a consistent order. 
%             For example for a 2x2 grid in [0,1] it would be xloc=[0 0 1 1]' and yloc=[0 1 0 1]'. 
%             The grid does not have to be regular or structured.

% Modify xloc and yloc for your own example

Nx =100; Ny = 100; N = Nx*Ny;
x = linspace(0,1,Nx);
y = linspace(0,1,Ny);
[xloc,yloc] = meshgrid(x,y);
xloc = xloc(:);  yloc = yloc(:);

% Modify H, nCheb and PringFlag for your own example

H = ones(N,100);    % right muliplier H, each column is a Nx1 vector
nCheb = 6;          % number of Chebyshev node
PrintFlag = true;   % print exact computation time and accuracy

if TestingMode
  %% testing mode 
  % Compute matrix-matrix product QH of dimension 10000x100
  eval(['[QH,QHexact] = ',ExecFile,'(xloc, yloc,H,nCheb,PrintFlag);']);
else
  %% application mode
  eval(['QH = ',ExecFile,'(xloc, yloc,H,nCheb,PrintFlag);']);
end

end
