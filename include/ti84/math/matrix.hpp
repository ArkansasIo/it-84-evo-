#pragma once
#include <vector>
#include <cstddef>
#include "ti84/core/result.hpp"
namespace ti84 {
class Matrix {
public:
 Matrix(std::size_t rows,std::size_t cols,double initial=0.0);
 std::size_t rows()const noexcept{return rows_;} std::size_t cols()const noexcept{return cols_;}
 double& at(std::size_t r,std::size_t c); double at(std::size_t r,std::size_t c)const;
 Result<Matrix> multiply(const Matrix& other)const; Result<double> determinant()const;
private:std::size_t rows_,cols_;std::vector<double> data_;
};
}
