// A simplefunction.cpp that takes 3 arguments
// 1) A function handle  (kernel of Q)
// 2) An integer value M (dimension of Q)
// 3) An integer value N (number of columns of H)
// 4) A matrix U of size MxN
// 5) A vector of location x of Mx1
// 6) A vector of location y of Nx1
// and returns the output of the product QU
// Usage:
//mex('-largeArrayDims','-I/Users/yueli/Dropbox/Matlab/FastKF/Final_code/mexFMM/eigen','gatewayfunction.cpp')

#include <iostream>
#include "math.h"
#include "mex.h"
#include "matrix.h"
#include "environment.hpp"
#include "BBFMM2D.hpp"
#include <Eigen/Core>
// include source file

using namespace Eigen;
using namespace std;
double pi 	=	4.0*atan(1);
extern void _main();

// Compute kernel value
void kernel_2D(const unsigned long M, double *x1, const unsigned long N, double *x2, double *Q, const mxArray *kernel){
    // prepare for mexCallMATLAB: val = feval(@fh, rSquare)
    mxArray *lhs,*rhs[2];
    rhs[0] = mxDuplicateArray(kernel);
    rhs[1] = mxCreateDoubleScalar(1);
    double *xptr = mxGetPr(rhs[1]) + 1;
    double rSquare;
    
    clock_t start = clock();
    for( int i=0; i<M; ++i){
        for(int j=0; j<N; ++j){
            rSquare = (x1[i]-x2[j])*(x1[i]-x2[j]);
            *xptr = rSquare;
            mexCallMATLAB(1,&lhs,2,rhs,"feval"); // feval(kernel,h)
            Q[j + N*i] = *mxGetPr(lhs);
            mxDestroyArray(lhs);
        }
    }
    clock_t end = clock();
    double QTimeInMEX = double(end-start)/double(CLOCKS_PER_SEC);
    cout << endl << "Total time taken for computing Q in C++ is: " << QTimeInMEX << endl;    
    
    //Clean up heap
    mxDestroyArray(rhs[0]);
    mxDestroyArray(rhs[1]);
}

void ckernel_2D(const unsigned long M, double *x1, const unsigned long N, double *x2, double *Q){
//     compute Q in C++
    double rSquare;
    clock_t start = clock();
    for( int i=0; i<M; ++i){
        for(int j=0; j<N; ++j){
            rSquare = (x1[i]-x2[j])*(x1[i]-x2[j]);
            Q[j + N*i] = rSquare*rSquare;
        }
    }
    clock_t end = clock();
    double QTimeInC = double(end-start)/double(CLOCKS_PER_SEC);
    cout << endl << "Total time taken for computing Q in C++ is: " << QTimeInC << endl;
}

void mexFunction(int nlhs,mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Macros for the output and input arguments
    #define Q_OUT     plhs[0]
    #define kernel    prhs[0]
    #define x_IN      prhs[1]
    #define y_IN      prhs[2]
    #define H_IN      prhs[3]

    double *x1, *x2;
//    int m, n;
    double *Qp;
    unsigned long N;
//    vector<Point> location;
    unsigned long m;
    double* charges;
    
    // Argument Checking:
//   // First Argument should be a Function Handle
    if( !mxIsClass( kernel , "function_handle")) {
        mexErrMsgTxt("First input argument is not a function handle.");
    }
    
//   // Second Argument is a Double Scalar
//   if (!mxIsClass(prhs[1], "double")||(mxGetM(prhs[1])>1)||(mxGetN(prhs[1])>1)) {
//     mexErrMsgTxt("Second input argument is not a double scalar.");
//   }
    // First and Second Argument are integer
    
    if( !mxIsDouble(x_IN)) {
        mexErrMsgTxt("Third input argument is not a real 2D full double array.");
    }
    if( !mxIsDouble(y_IN)) {
        mexErrMsgTxt("Third input argument is not a real 2D full double array.");
    }
    if( !mxIsDouble(H_IN)) {
        mexErrMsgTxt("Third input argument is not a real 2D full double array.");
    }
    
    //processing on input arguments
    N = mxGetM(H_IN); // get the first dimension of H
    m = mxGetN(H_IN); // get the second dimension of H
    x1 = mxGetPr(x_IN);
    x2 = mxGetPr(y_IN);
    cout << x1[N-1] << " " << x2[m-1] <<endl;
    
    // Output Argument
//    Q_OUT = mxCreateDoubleScalar(*mxGetPr(lhs));
     Q_OUT = mxCreateDoubleMatrix(N,N, mxREAL); // Create the output matrix
    Qp = mxGetPr(Q_OUT);
    kernel_2D(N,x1,N,x2,Qp,kernel);
    ckernel_2D(N,x1,N,x2,Qp);
    
    // Read Binary file
    unsigned long P;
    vector<Point> location;
    unsigned p;

    string filenameLocation     =   "../input/LOC.bin";
    string filenameH            =   "../input/U.bin";
    string filenameMetadata     =   "../input/meta.txt";
    
    read_Metadata_BBFMM2D (filenameMetadata, P, p);
    cout <<P << " " << p <<endl;

    return;
}