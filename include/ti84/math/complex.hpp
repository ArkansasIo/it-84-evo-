#pragma once
#include <complex>
#include "ti84/core/result.hpp"
namespace ti84 {
using Complex = std::complex<double>;
Complex conjugate(Complex value) noexcept;
double magnitude(Complex value) noexcept;
double argument(Complex value) noexcept;
Result<Complex> divide(Complex numerator,Complex denominator);
}
