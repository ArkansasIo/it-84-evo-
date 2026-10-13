#include "ti84/math/numerical.hpp"
#include <cmath>
#include <utility>
namespace ti84 {
Result<double> derivative(const ScalarFunction& f,double x,double h){
 if(!f||!std::isfinite(x)||!std::isfinite(h)||h<=0)return Result<double>::failure("Derivative requires a function, finite x, and positive step");
 const double l=f(x-h),r=f(x+h);if(!std::isfinite(l)||!std::isfinite(r))return Result<double>::failure("Function is not finite near derivative point");
 return Result<double>::success((r-l)/(2*h));
}
Result<double> integrateSimpson(const ScalarFunction& f,double a,double b,unsigned n){
 if(!f||!std::isfinite(a)||!std::isfinite(b)||n==0||n>10000000)return Result<double>::failure("Invalid integration arguments");
 if(n%2)++n;const double h=(b-a)/n;double sum=f(a)+f(b);
 for(unsigned i=1;i<n;++i){double y=f(a+h*i);if(!std::isfinite(y))return Result<double>::failure("Non-finite function value during integration");sum+=(i%2?4:2)*y;}
 const double result=sum*h/3;if(!std::isfinite(result))return Result<double>::failure("Integration result is not finite");return Result<double>::success(result);
}
Result<double> solveBisection(const ScalarFunction& f,double a,double b,double tol,unsigned maxIt){
 if(!f||!std::isfinite(a)||!std::isfinite(b)||a>=b||tol<=0||maxIt==0)return Result<double>::failure("Invalid bisection arguments");
 double fa=f(a),fb=f(b);if(!std::isfinite(fa)||!std::isfinite(fb))return Result<double>::failure("Endpoint values must be finite");
 if(fa==0)return Result<double>::success(a);if(fb==0)return Result<double>::success(b);if(std::signbit(fa)==std::signbit(fb))return Result<double>::failure("Interval does not bracket a root");
 for(unsigned i=0;i<maxIt;++i){double m=a+(b-a)/2,fm=f(m);if(!std::isfinite(fm))return Result<double>::failure("Function is not finite inside interval");if(std::abs(fm)<=tol||std::abs(b-a)<=tol)return Result<double>::success(m);if(std::signbit(fa)!=std::signbit(fm)){b=m;fb=fm;}else{a=m;fa=fm;}}
 return Result<double>::failure("Bisection did not converge within iteration limit");
}
}
