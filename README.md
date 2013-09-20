mexBBFMM2D
==========

This is the Matlab MEX gateway files to the package BBFMM2D (https://github.com/sivaramambikasaran/BBFMM2D).
BBFMM2D provides a *O(NlogN)* solution to compute matrix-matrix product Q*H, where Q is a covariance 
matrix of size NxN with a kernel, and N is the number of unknown values at points (x,y) in a 2D domain. 
H is a N x m matrix with N >> m. 
The kernel is a decaying function of the seperation between two points and takes value from [0,1].  

Setup mex on your computer by typing in Matlab  

```
      mex -setup 
```
More details can be found in (http://www.mathworks.com/help/matlab/matlab_external/building-mex-files.html#brnq88l-1)
For Mac users who find troubles with mex setup, a helpful link is
http://www.mathworks.com/support/solutions/en/data/1-FR6LXJ/

Setup:
+ Download [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)
+ Download [BBFMM2D](https://github.com/sivaramambikasaran/BBFMM2D), and put it under _eigen/Codes_
+ Download [mexBBFMM2D](https://github.com/whereisdodo/mexBBFMM2D), and put it under _BBFMM2D/_

Try an example:
+ Go to BBFMM2D/, and type Matlab command  

```
      callmxFMM2D.m
```

To compile the code yourself:

1.Go to the folder _mexBBFMM2D/_
```
      syms r
      kernel = exp(-r/30);
      make(r,kernel)
```
2.You should find _mexBBFMM2D.mex_ in your folder, now if you want to compute a matrix-matrix product Q*H, add the following 
code into your matlab script  

```
      addpath(Directory to mexBBFMM2D);
      QH = mexBBFMM2D(xloc,yloc,H,nCheb); 
      
```
  Or if you want to compare the result with exact product QHexact for smaller case to determine the least number of chebyshev nodes needed. Large nCheb will give greater accuracy but more time consuming.
```
      [QH,QHexact] = mexBBFMM2D(xloc,yloc,H,nCheb);
```
3.For a new kernel type, repeat step 1 to 2. Otherwise no need to recompile the code. 
