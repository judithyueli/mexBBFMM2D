% this file will call mexBBFMM2D.cpp
src1 = '../src/H2_2D_Tree.cpp';
src2 = '../src/H2_2D_Node.cpp';
src3 = '../src/kernel_Base.cpp';
src4 = '../src/kernel_Types.cpp';
src5 = '../src/read_metadata_BBFMM2D.cpp';
src6 = '../src/write_Into_Binary_File.cpp';
eigenDIR = '../../../';
fmmDIR = '../header/';
mex('-O','gatewayfunction.cpp',src1,src2,src3,src4,src5,src6,'-largeArrayDims',['-I' eigenDIR],['-I' fmmDIR])
clear src1 src2 src3 src4 src5 src6 eigenDIR fmmDIR