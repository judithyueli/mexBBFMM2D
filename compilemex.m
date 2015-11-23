% Compile mex code for new kernel
syms r;                         % seperation between two points
kernel = exp(-sqrt(r^0.5)/30);  % user input here, kernel has to be a symbolic function
outputfile = 'case1_test';
make(r,kernel,outputfile);