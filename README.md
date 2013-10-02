mexBBFMM2D
==========

This is the Matlab MEX gateway files to the package [BBFMM2D](https://github.com/sivaramambikasaran/BBFMM2D).
BBFMM2D provides a *O(NlogN)* solution to compute matrix-matrix product Q*H, where Q is a covariance 
matrix of size NxN with a kernel, and N is the number of unknown values at points (x,y) in a 2D domain. 
H is a N x m matrix with N >> m. 
The kernel is a decaying function of the seperation between two points and takes value from [0,1].  

###STEP 1: Setup MEX

This package relies on MATLAB MEX functions. In order to use MEX functions, you should setup mex correctly.

- Select a C compiler for the MATLAB version and the operation systems installed on your computer. For a list of MATLAB supported compiler, visit [here](http://www.mathworks.com/support/sysreq/previous_releases.html)

- Setup MEX by typing the following MATLAB command

```
      mex -setup 
```

- To ensure you have MEX installed appropriately, try an example provided by MATLAB:

```
	copyfile([matlabroot,'/extern/examples/mex/arraySize.c'],'./','f')
	mex -v arraySize.c
	arraySize(5000)
```
You would be able to see the size of a 5000 x 5000 matrix.

###STEP2: Try the example problem given by mexBBFMM2D

- Download the package from this link.

- Go to the folder containing `mexFMM2D.cpp`, and type Matlab command  

```
      callmxFMM2D
```

The output `QHexact` will be the exact product of a 10000 x 10000 covariance matrix `Q` with kernel $$(exp(-\dfrac{\sqrt{h}}{30})$$ and a 10000x100 matrix `H`. `QH` will be the product computed using BBFMM2D package.  

### Step 3: Use mexBBFMM2D for your own research problem:

1.Go to the folder _mexBBFMM2D/_
```
      syms r
      kernel = exp(-r/30);
      make(r,kernel,'expfun')
```
2.You should find _expfun.mex_ in your folder, now if you want to compute a matrix-matrix product Q*H, add the following 
code into your matlab script  

```
      addpath(Directory to mexBBFMM2D);
      QH = expfun(xloc,yloc,H,nCheb); 
      
```
  Or if you want to compare the result with exact product QHexact for smaller case to determine the least number of chebyshev nodes needed. Large `nCheb` will give greater accuracy but more time consuming.
```
      [QH,QHexact] = expfun(xloc,yloc,H,nCheb);
```
3.For a new kernel type, repeat step 1 to 2. Otherwise no need to recompile the code. 

#### This package uses:

1. [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)

2. [BBFMM2D](https://github.com/sivaramambikasaran/BBFMM2D)

<script type="text/javascript"
   src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
