function make(var,kernel,filename)
% Produce mex file with 'filename' for the input kernel. File extension is automatically added. 
% For each new kernel type, run this make file first before call mexFMM2D. 
% The new kernel will be embedded in a new file 'kernelfun.hpp'

% Usage:
% syms r; f = exp(-abs(r)/30); filename = 'expfun';
% make(r,f,filename)

%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%Main Function%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%

% convert kernel to C readable format
var = char(var);
ckernel = ccode(kernel);

% Pass the Kernel to kernelfun.hpp
fid = fopen('kernelfun.hpp','w+');
fprintf(fid,'class myKernel: public kernel_Base {\n');
fprintf(fid,'public:\n');
fprintf(fid,'    virtual double kernel_Func(Point r0, Point r1){\n');
fprintf(fid,'        double %s =  sqrt((r0.x-r1.x)*(r0.x-r1.x) + (r0.y-r1.y)*(r0.y-r1.y));\n',var);
fprintf(fid,'        double t0;         //implement your own kernel on the next line\n');
fprintf(fid,'        %s\n',ckernel);
fprintf(fid,'        return t0;\n');
fprintf(fid,'    }\n');
fprintf(fid,'};\n');
fclose(fid);

% this file will call mexBBFMM2D.cpp
src1 = 'BBFMM2D/src/H2_2D_Tree.cpp';
src2 = 'BBFMM2D/src/H2_2D_Node.cpp';
src3 = 'BBFMM2D/src/kernel_Base.cpp';
src4 = 'BBFMM2D/src/kernel_Types.cpp';
eigenDIR = 'eigen/';
fmmDIR = 'BBFMM2D/header/';
mex('-O','mexFMM2D.cpp',src1,src2,src3,src4,'-largeArrayDims',['-I',eigenDIR],['-I',fmmDIR],'-output',filename)
disp('mex compiling is successful! You can call mexFMM2D now')
end
