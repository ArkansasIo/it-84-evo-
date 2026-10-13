#include "ti84/math/complex.hpp"
#include <cmath>
namespace ti84 {
Complex conjugate(Complex z)noexcept{return std::conj(z);}
double magnitude(Complex z)noexcept{return std::abs(z);}
double argument(Complex z)noexcept{return std::arg(z);}
Result<Complex> divide(Complex a,Complex b){if(std::norm(b)==0.0)return Result<Complex>::failure("Complex division by zero");Complex z=a/b;if(!std::isfinite(z.real())||!std::isfinite(z.imag()))return Result<Complex>::failure("Complex division result is not finite");return Result<Complex>::success(z);}
}
