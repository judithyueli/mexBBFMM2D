##Quick Start Guild for mexBBFMM2D, a Matlab interface for Black Box Fast Multipole Method (BBFMM2D)  
==========

###Function
Perform fast multiplication of a kernel Q with a vector or matrix, P = QH

###Overview
The Fast Multipole Method is an algorithm that can be used to perform fast multiplication of an N x N dense matrix Q(x,y) where N is the number of unknown values at points (x,y) in a 2D domain, with a matrix H of size N x m (N>>m). The direct multiplication approach has complexity O(N^2), while the BBFMM2D has linear complexity O(N). As an example, for a matrix of size 10,000x10,000 multiplied by 10,000 x 100, the BBFMM2D takes 1.4 seconds, while the direct approach takes 8.1 seconds, on a single processor laptop. The table below shows computation time on a single core CPU.

|   N      |  Time in seconds  |     
| -------: |:-----------------:|   
| 10,000   |                1.4|
| 100,000  |               11.4|  
| 1000,000 |             126.2 |

BBFMM2D is written in C++ (https://github.com/sivaramambikasaran/BBFMM2D). For usage within a Matlab code,  the mexBBFMM2D can be used, which is the Matlab MEX gateway files to the package BBFMM2D.

The FMM performs the multiplication by an approximation that relies on Chebyshev interpolation to construct low-rank approximations for well-separated clusters of the kernel. In addition the use of Singular Value Decomposition ensures that the computational cost is minimal. The method has an approximation error that can be controlled by input parameters, which can be adjusted depending on the accuracy required.  

###Disclaimer

This is a quick-start guide with easy to follow instructions on how to set up and use mexBBFMM2D in Matlab, with an example m-file that can be used to perform matrix-vector and matrix-matrix multiplication. A reasonably good knowledge of Matlab is assumed and minimal understanding of the FMM  theory is needed.  

For a more involved description of the code and the method please see [here](https://github.com/sivaramambikasaran/BBFMM2D), and for a full description of the algorithm see __Reference__.

In this guide, we will use the example of the multiplication of a Gaussian covariance matrix Q (termed as Gaussian kernel) with a matrix H. The method can also be applied for other smooth kernels (see Appendix).

###Quick start guide

####Step 1:  Download the code and supporting software

####Step 1a:  Check if you have MEX and MATLAB Symbolic Math Toolbox set up in Matlab

This package relies on MATLAB MEX functions and MATLAB Symbolic Math Toolbox. In order to use MEX functions, you should setup mex.

Setup MEX by typing the following MATLAB command
```
      mex -setup  
```

If you get an error saying that SDK files are missing (e.g. ... Looking for folder '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk' ...No.) you can find the sdk files here https://github.com/phracker/MacOSX-SDKs/releases. Download those that are missing and place them in the appropriate directories based on the error message you get. 

Once mex -setup runs successfully, to ensure that  MEX is installed, try an example provided by MATLAB:
```
copyfile([matlabroot,'/extern/examples/mex/arraySize.c'],'./','f')     
mex -v arraySize.c     
arraySize(5000) 
```

The last two lines of the screen output should read  

```
Dimensions: 5000x5000
Size of  array in kilobytes: 24414
```

If you have trouble with setting up mex, see [here](http://www.mathworks.com/support/sysreq/previous_releases.html)

####Step 1b:  Download the code from https://github.com/judithyueli/mexBBFMM2D/archive/master.zip

A folder called `mexBBFMM2D` should appear, which includes the folders
`BBFMM2D\` and `Eigen\`, as well as an m-file called (`compilemex.m`) and an example m-file (`callmxFMM2D.m`) that we will use in this quick start quide. These files will be used to compile, set-up, test and use the `BBFMM2D`. The user only needs to change these m-files. No modifications will be needed to the contents of the folder `BBFMM2D` which includes the c++ source code. 

####Step 2: Compile the mex file

__A.__ Open file `compilemex.m`

__B.__ Determine your kernel expression (line 3) 

__C.__ Give your BBFMM2D case a name (line 4), e.g. 

```
kernel = exp(-sqrt(r^0.5)/30);
outputfile = 'case1';
```

Run compilemex.m. The code will compile and will create a function with the name `case1.mexmaci64` (the name will change depending on computer architecture).

NOTE!! This step should be performed every time the kernel Q is changed (because the mex file should be recompiled).


####Step 3: Run example

__Example filename:__ `callmxFMM2D.m`

__Example description:__ 
This example is for a 2D domain of size 100x100. The covariance matrix Q of this domain is of size 10000x10000. Running `mexBBFMM2D` will perform the multiplication of `Q` (as defined by the kernel in `compilemex.m`) with a matrix `H` given by ones(10000,100). 

`mexBBFMM2D` can be run in two modes, a testing mode and an application mode. 

__Testing mode:__

```
[QH,QHexact] = case1(xloc, yloc,H,nCheb,print);
```

In this mode, the code will multiply `Q` and `H` by both BBFMM2D and by direct multiplication and will compare the computational time for the two methods and give the approximation error of BBFMM2D. This mode is useful when one wants to determine how many Chebyshev nodes to use for a given approximation error and will take a long time because the direct multiplication is also performed. Caution! Do not use for large matrices because direct multiplication will take for ever. 

__Input__: 

`xloc`, `yloc`: These are the coordinates of each grid point. These are mx1 vectors arranged in a consistent order. For example for a 2x2 grid in [0,1] it would be xloc=[0 0 1 1]’ and yloc=[0 1 0 1]’. 

`H`: the matrix we want to multiply Q with (Q*H)

`nCheb`: number of Chebyshev nodes (the higher nCheb, the higher nCheb, the higher the accuracy, but higher the computational cost

`print`: flag for printing the output details

__Output:__ 

`QH`: the product of Q and H as given by BBFMM2D

`QHexact`: the product of Q and H by direct multiplication


Example results for `QH` with `nCheb`=4,5,6. Large `nCheb` will give greater accuracy but more time consuming. 

|   nCheb       | accuracy          |  Time(s) with BBFMM2D  | Time(s) with direct multiplication|     
| ------------: |:-----------------:|:----------------------:|:---------------------------------:|
| 4  		|        4.45E-08   |                   0.67s|                            8.01s|
| 5  		|       1.66E-09    |                   0.85s|                            8.06s|
| 6  		|      3.20E-10     |                   1.44s|                            8.34s|

__Application mode:__ 
```
QH = case1(xloc, yloc,H,nCheb,print);
```

Input: same as in testing mode. Only performs the multiplication using BBFMM2D and can be used for very large cases.

####Step 4: Run you own example

- Determine your kernel type and compile the mex file  (step 2)
- Set up your grid coordinates in two vectors x and y
- Run mexBBFMM2D in testing mode to determine number of Chebyshev modes
- Run mexBBFMM2D in application mode for your own example.


### APPENDIX

__Kernel Options__

`r` : distance between two points

`L` : length scale parameter

`\sigma^2`: variance parameter

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

#### Reference:
1. Sivaram Ambikasaran, Judith Yue Li, Peter K. Kitanidis, Eric Darve, Large-scale stochastic linear inversion using hierarchical matrices, Computational Geosciences, December 2013, Volume 17, Issue 6, pp 913-927 [link](http://link.springer.com/article/10.1007%2Fs10596-013-9364-0)
2. Judith Yue Li, Sivaram Ambikasaran, Eric F. Darve, Peter K. Kitanidis, A Kalman filter powered by H2-matrices for quasi-continuous data assimilation problems [link](https://www.dropbox.com/s/xxjdvixq7py4bhp/HiKF.pdf)
3. Saibaba, A., S. Ambikasaran, J. Li, P. Kitanidis, and E. Darve (2012), Application of hierarchical matrices to linear inverse problems in geostatistics, OGST Revue d’IFP Energies Nouvelles, 67(5), 857–875, doi:http://dx.doi.org/10.2516/ogst/2012064. [link](http://ogst.ifpenergiesnouvelles.fr/articles/ogst/abs/2012/05/ogst120061/ogst120061.html)
4. Fong, W., and E. Darve (2009), The black-box fast multipole method, Journal of Computational Physics, 228(23), 8712–8725.[link](http://www.logos.t.u-tokyo.ac.jp/~tau/Darve_bbfmm_2009.pdf)

<script type="text/javascript"
   src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
