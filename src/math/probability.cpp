#include "ti84/math/probability.hpp"
#include <cmath>
#include <limits>
namespace ti84 {
Result<double> normalPdf(double x,double mean,double sd){
 if(!std::isfinite(x)||!std::isfinite(mean)||!std::isfinite(sd)||sd<=0)return Result<double>::failure("Normal distribution requires finite values and standard deviation > 0");
 constexpr double invSqrt2Pi=0.39894228040143267794;double z=(x-mean)/sd;return Result<double>::success(invSqrt2Pi/sd*std::exp(-0.5*z*z));
}
Result<double> normalCdf(double x,double mean,double sd){
 if(!std::isfinite(x)||!std::isfinite(mean)||!std::isfinite(sd)||sd<=0)return Result<double>::failure("Normal distribution requires finite values and standard deviation > 0");
 return Result<double>::success(0.5*std::erfc(-(x-mean)/(sd*std::sqrt(2.0))));
}
Result<double> binomialPmf(unsigned n,unsigned k,double p){
 if(k>n)return Result<double>::success(0.0);if(!std::isfinite(p)||p<0||p>1)return Result<double>::failure("Probability must be in [0,1]");
 if(p==0)return Result<double>::success(k==0?1.0:0.0);if(p==1)return Result<double>::success(k==n?1.0:0.0);
 // Log-gamma avoids overflowing the integer binomial coefficient.
 const double logChoose=std::lgamma(n+1.0)-std::lgamma(k+1.0)-std::lgamma(n-k+1.0);
 const double value=std::exp(logChoose+k*std::log(p)+(n-k)*std::log1p(-p));
 if(!std::isfinite(value))return Result<double>::failure("Binomial probability calculation overflowed");
 return Result<double>::success(value);
}
}
