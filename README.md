mexBBFMM2D
==========

This is the Matlab MEX gateway files to the package [BBFMM2D](https://github.com/sivaramambikasaran/BBFMM2D).
BBFMM2D provides a *O(NlogN)* solution to compute matrix-matrix product Q*H, where Q is a covariance 
matrix of size NxN with a kernel, and N is the number of unknown values at points (x,y) in a 2D domain. 
H is a N x m matrix with N >> m. 
The kernel is a decaying function of the seperation between two points and takes value from [0,1].  

This package relies on MATLAB MEX functions. In order to use MEX functions, you should setup mex correctly.

1. Select a C compiler for the MATLAB version and the operation systems installed on your computer. For a list of MATLAB supported compiler, visit [here](http://www.mathworks.com/support/sysreq/previous_releases.html)

2. Setup MEX by typing the following MATLAB command
```
      mex -setup 
```

3. To ensure you have MEX installed appropriately, try an example provided by MATLAB:

```
	cd(fullfile(matlabroot, 'extern', 'examples', 'mex'))
	mex -v yprime.c
```

You would be able to see yprime.mex in your local folder, then you can call yprime
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

This package uses:

1. [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)

2. [BBFMM2D](https://github.com/sivaramambikasaran/BBFMM2D)
