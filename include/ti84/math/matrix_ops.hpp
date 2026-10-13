#pragma once
#include "ti84/math/matrix.hpp"
namespace ti84 {
Result<Matrix> transpose(const Matrix& input);
Result<Matrix> inverse(const Matrix& input,double epsilon=1e-12);
Result<Matrix> reducedRowEchelonForm(const Matrix& input,double epsilon=1e-12);
}
