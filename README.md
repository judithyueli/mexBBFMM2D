mexBBFMM2D
==========

This is the Matlab MEX gateway files to the package [BBFMM2D](https://github.com/sivaramambikasaran/BBFMM2D).
BBFMM2D provides a __O(N)__ solution to compute matrix-matrix product Q*H, where Q is a covariance 
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

The output `QHexact` is the exact product of a 10000 x 10000 covariance matrix `Q` with kernel ![equation](http://latex.codecogs.com/gif.latex?Q%28h%29%20%3D%20%5Cexp%28-%5Cdfrac%7B%5Csqrt%7Bh%7D%7D%7B30%7D%29) and a 10000 x 100 matrix `H`. And `QH` is the product computed using BBFMM2D package. The relative difference of `QH` and `QHexact` is __3.2E-10__. The table below shows computation time on a single core CPU.

|   N      |  Time in seconds  |     
| -------: |:-----------------:|   
| 10,000   |                2.6|
| 100,000  |               27.3|  
| 1000,000 |              242.5|   

### Step 3: Use mexBBFMM2D for your own research problem:

1.Compile: Go to the folder __mexBBFMM2D/__ 
```
      syms r                     % r is seperation 
      kernel = exp(-r/30);       % specify kernel type
      make(r,kernel,'expfun')    % compile and generate the mex file with name 'expfun'
```

2.You should find __expfun.mex__ in your folder, now if you want to compute a matrix-matrix product Q*H, add the following code into your matlab script  

```
      addpath(Directory to expfun.mex);
      clear QH;                           % Clear memory associated with output
      QH = expfun(xloc,yloc,H,nCheb);       
```
  Or if you want to compare the result with exact product QHexact for smaller case to determine the least number of chebyshev nodes `nCheb` needed. Large `nCheb` will give greater accuracy but more time consuming. `nCheb` should be greater than 3.
```
      [QH,QHexact] = expfun(xloc,yloc,H,nCheb);
```

3.For a new kernel type, repeat step 1 to 2. Otherwise step 1 can be skipped. 

#### Example of kernel type:
+ Gaussian kernel 

      ![guasskernel](http://latex.codecogs.com/gif.latex?%5Cdpi%7B150%7D%20Q%28r%29%20%3D%20%5Csigma%5E2%20%5Cexp%28-%5Cdfrac%7Br%5E2%7D%7BL%5E2%7D%29)

+ Exponential kernel

      ![expkernel](http://latex.codecogs.com/gif.latex?%5Cdpi%7B150%7D%20Q%28r%29%20%3D%20%5Cexp%28-%5Cdfrac%7Br%7D%7BL%7D%29)

+ Logrithm kernel

      ![logkernel](http://latex.codecogs.com/gif.latex?%5Cdpi%7B150%7D%20Q%28r%29%20%3D%20A%20%5Clog%28r%29%2C%20A%3E0)

+ Linear kernel

      ![linearkernel](http://latex.codecogs.com/gif.latex?%5Cdpi%7B150%7D%20Q%28r%29%20%3D%20%5Ctheta%20r%2C%20%5Ctheta%20%3E0)

+ Power kernel

      ![powerkernel](http://latex.codecogs.com/gif.latex?%5Cdpi%7B150%7D%20Q%28r%29%20%3D%20%5Ctheta%20r%5Es%2C%20%5Ctheta%20%3E0%2C%200%20%3Cs%20%3C2)
      
#### This package uses:

1. [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)

2. [BBFMM2D](https://github.com/sivaramambikasaran/BBFMM2D)

<script type="text/javascript"
   src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
