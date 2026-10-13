#pragma once
#include <functional>
#include "ti84/core/result.hpp"
namespace ti84 {
using ScalarFunction = std::function<double(double)>;
Result<double> derivative(const ScalarFunction& f,double x,double step=1e-5);
Result<double> integrateSimpson(const ScalarFunction& f,double a,double b,unsigned intervals=1000);
Result<double> solveBisection(const ScalarFunction& f,double a,double b,double tolerance=1e-9,unsigned maxIterations=200);
}
