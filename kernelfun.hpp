class myKernel: public kernel_Base {
public:
    virtual double kernel_Func(Point r0, Point r1){
        double r =  sqrt((r0.x-r1.x)*(r0.x-r1.x) + (r0.y-r1.y)*(r0.y-r1.y));
        double t0;         //implement your own kernel on the next line
          t0 = exp(-r*r);
        if (isinf(t0)|| isnan(t0))
           return 0;
        else
        return t0;
    }
};
