##Trouble shooting for  mexBBFMM2D
==========
####__mexBBFMM2D__ has been tested on the following platform:

- OS X Yosemite (10.10.5) with MATLAB R2015b
- Windows 7 with MATLAB R2014b

Report any additional issues to yuel@stanford.edu if the error you've got is not covered in this trouble shooting guide.

####Understanding your error messages
See [here](http://www.mathworks.com/help/matlab/matlab_external/understanding-mex-file-problems.html) for a general guide for MEX troubleshooting.
- Can you compile and run the `arraySize.c` example? If no check out if your compiler is supported by MATLAB, see question __How do I find the correct C/C++ compiler__. 
- Can you compile and run the `compilemex.m`? If you have no trouble running `arraySize.c` but have trouble run `compilemex.m` shoot us an email

####How do I find the correct C/C++ compiler?
See [here](http://www.mathworks.com/support/sysreq/previous_releases.html) for a list of supported C/C++ compiler for different MATLAB version. Type `mex.getCompilerConfigurations` to get details of your compilers. 

__Microsoft Windows SDK 7.1__ is a free compiler supported by most MATLAB version and across platform. If you have trouble installing SDK 7.1, or have trouble running it on Windows see [here](http://www.mathworks.com/matlabcentral/answers/95039-why-does-the-sdk-7-1-installation-fail-with-an-installation-failed-message-on-my-windows-system)

###Errors related to SDK compiler
#### __For Mac:__ If you get an error saying that SDK files are missing, e.g.,  

```
Looking for folder '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk' ...No. 
```

you can find the sdk files here https://github.com/phracker/MacOSX-SDKs/releases. Download those that are missing and place them in the appropriate directories based on the error message you get. 

#### __For PC:__ If you get an error related to 'ammintrin.h':
```
Building with 'Microsoft Windows SDK 7.1 (C++)'.
Error using mex
mexFMM2D.cpp
c:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\intrin.h(26) : fatal error C1083: Cannot open
include file: 'ammintrin.h': No such file or directory
 
Error in make (line 38)
mex('-O','mexFMM2D.cpp',src1,src2,src3,'-largeArrayDims',['-I',eigenDIR],['-I',fmmDIR],'-output',filename)
 
Error in compilemex (line 5)
make(r,kernel,outputfile);
```
See [here](http://www.mathworks.com/matlabcentral/answers/90383-fix-problem-when-mex-cpp-file) or copy `ammintrin.h` from elsewhere in your computer (usually you will have multiple versions of `ammintrih.h`) and put it in the directory shown up in the error message, e.g., `c:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\`


#### Error related to "mex -largeArrayDims"

mexBBFMM2D package use `mex -largeArrayDims`. `largeArrayDims` is a MEX flag that add after MATLAB version 7.3., see more details [here](http://www.mathworks.com/matlabcentral/answers/99144-how-do-i-update-mex-files-to-use-the-large-array-handling-api-largearraydims)




