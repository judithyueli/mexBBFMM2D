function make(var,kernel)
% Produce mex file 'mexFMM2D' for the input kernel. For each new kernel
% type, run this make file first before call mexFMM2D. 
% The new kernel will be embedded in a new file 'kernelfun.hpp'
% Usage:
% syms r; f = exp(-abs(r)/30);
% make(r,f)

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
src1 = '../src/H2_2D_Tree.cpp';
src2 = '../src/H2_2D_Node.cpp';
src3 = '../src/kernel_Base.cpp';
src4 = '../src/kernel_Types.cpp';
eigenDIR = '../../../';
fmmDIR = '../header/';
mex('-O','mexFMM2D.cpp',src1,src2,src3,src4,'-largeArrayDims',['-I' eigenDIR],['-I' fmmDIR])
disp('mex compiling is successful! You can call mexFMM2D now')
% clear src1 src2 src3 src4 src5 src6 eigenDIR fmmDIR
end
