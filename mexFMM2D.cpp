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

/*! Define user's own kernel */
class myKernel: public kernel_Base {
public:
    virtual double kernel_Func(Point r0, Point r1){
        //implement your own kernel here
        double rSquare  =   (r0.x-r1.x)*(r0.x-r1.x) + (r0.y-r1.y)*(r0.y-r1.y);
        return exp(-pow(pow(rSquare,0.5)/900.0,0.5));
    }
};

// Pass location from matlab to C
void read_location(const mxArray* x, const mxArray* y, vector<Point>& location){
    unsigned long N;
    double *xp, *yp;
    N = mxGetM(x);
    xp = mxGetPr(x);
    yp = mxGetPr(y);
    for (unsigned long i = 0; i < N; i++){
        Point new_Point;
        new_Point.x = xp[i];
        new_Point.y = yp[i];
        location.push_back(new_Point);
    }
}
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

// compute the exact Q in C++ 
void ckernel_2D(const unsigned long M, const vector<Point>& r0, const unsigned long N, const vector<Point>& r1, Map<MatrixXd> Q){
    double rSquare;
    clock_t start = clock();
    for( int i=0; i<M; ++i){
        for(int j=0; j<N; ++j){
            rSquare = (r0[i].x-r1[j].x)*(r0[i].x-r1[j].x) + (r0[i].y - r1[j].y)*(r0[i].y - r1[j].y);
            // Q[j + N*i] = rSquare*rSquare;
            Q(i,j) = exp(-pow(pow(rSquare,0.5)/900.0,0.5));
        }
    }
    clock_t end = clock();
    double QTimeInC = double(end-start)/double(CLOCKS_PER_SEC);
    cout << endl << "Total time taken for computing Q in C++ is: " << QTimeInC << endl;
}

void mexFunction(int nlhs,mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Macros for the output and input arguments
    #define Q_OUT     plhs[0]
    #define QH_OUT    plhs[1]
    #define kernel    prhs[0]
    #define x_IN      prhs[1]
    #define y_IN      prhs[2]
    #define H_IN      prhs[3]

    unsigned long N;
    unsigned long m;
    
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
    vector<Point> location;
    read_location(x_IN,y_IN,location);


    // Output Argument
//    Q_OUT = mxCreateDoubleScalar(*mxGetPr(lhs));
    // Q_OUT = mxCreateDoubleMatrix(N,N, mxREAL); // Create the output matrix
    // double *Qp = mxGetPr(Q_OUT);
    
    
    // compute exact matrix vector product
    // myKernel A;
    //MatrixXd Q;
    //Q = MatrixXd::Zero(N,N);
    // ckernel_2D(N,x1,N,x2,Q);
    // Create an uninitialized numeric array for dynamic memory allocation
    Q_OUT = mxCreateNumericMatrix(0, 0, mxDOUBLE_CLASS, mxREAL);
    // Create a local C array to load H and Q
    double *Qp, *charges;
    Qp = (double *) mxMalloc(N * N * sizeof(double));  // +1 is nessessary?
    charges = mxGetPr(H_IN);
    // Load data to local array using Eigen <Map>
    Map<MatrixXd> Q(Qp,N,N);
    Map<MatrixXd> H(charges,N,m);
    // Compute exact covariance Q
    cout << "Starting Exact computation..." << endl;
    clock_t start = clock();
    ckernel_2D(N,location,N,location,Q);
    clock_t end = clock();
    double exactAssemblyTime = double(end-start)/double(CLOCKS_PER_SEC);
    // Compute exact Matrix vector product
    start = clock();
    QH_OUT = mxCreateNumericMatrix(0, 0, mxDOUBLE_CLASS, mxREAL);
    double *QHp;
    QHp = (double *) mxMalloc(N * m * sizeof(double));
    Map<MatrixXd> QHT(QHp,N,m);
    QHT = Q*H;
    end = clock();
    double exactComputingTime = double(end-start)/double(CLOCKS_PER_SEC);

    cout << "the total computation time is " << exactAssemblyTime + exactComputingTime <<endl;
    // Put the C array into the mxArray and define its dimension
    mxSetPr(Q_OUT,Qp); // Qp must be initialiezed using mxMalloc
    mxSetM(Q_OUT,N);
    mxSetN(Q_OUT,N);
    mxSetPr(QH_OUT,QHp);
    mxSetM(QH_OUT,N);
    mxSetN(QH_OUT,m);

    return;
}