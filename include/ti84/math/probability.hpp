#pragma once
#include "ti84/core/result.hpp"
namespace ti84 {
Result<double> normalPdf(double x,double mean=0.0,double standardDeviation=1.0);
Result<double> normalCdf(double x,double mean=0.0,double standardDeviation=1.0);
Result<double> binomialPmf(unsigned trials,unsigned successes,double probability);
}
