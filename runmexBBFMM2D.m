function QH = runmexBBFMM2D(xloc, yloc,H,nCheb,PrintFlag,execname,TestingMode)

%This function can be run in testing mode and application mode
% -----------
%Input:  
% Grid information - regular 100x100 grid in [0,1]
% xloc, yloc: These are the coordinates of each grid point provided as vectors. 
%             These are m x 1 vectors arranged in a consistent order. 
%             For example for a 2x2 grid in [0,1] it would be xloc=[0 0 1 1]' 
%             and yloc=[0 1 0 1]'. 
%             The grid does not have to be regular or structured.
% H: the matrix we want to multiply Q with (multiply Q with H)
% nCheb: number of Chebyshev nodes (the higher nCheb, the higher the accuracy,
%        but higher the computational cost), integers between 4 to 6 are suggested.
%        Try starting with 4 and increase to achieve desirable accuracy.
% PrintFlag: flag for printing the output details
% -----------
% Output: product QH with BBFMM2D (application mode) 
%         product QH with BBFMM2D and QHexact with direct multiplication (testing mode)

if TestingMode
  %% testing mode 
  % Compute matrix-matrix product QH of dimension 10000x100
  eval(['[QH,QHexact] = ',execname,'(xloc, yloc,H,nCheb,PrintFlag);']);
else
  %% application mode
  eval(['QH = ',execname,'(xloc, yloc,H,nCheb,PrintFlag);']);
end
