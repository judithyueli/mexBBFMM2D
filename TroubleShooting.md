##Trouble shooting for  mexBBFMM2D
==========

####How do I find the correct C++ compiler?

See [here](http://www.mathworks.com/support/sysreq/previous_releases.html)

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

See [here](http://www.mathworks.com/matlabcentral/answers/90383-fix-problem-when-mex-cpp-file)


