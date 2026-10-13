#include "ti84/math/matrix.hpp"
#include <cmath>
#include <algorithm>
namespace ti84 {
Matrix::Matrix(std::size_t r,std::size_t c,double v):rows_(r),cols_(c),data_(r*c,v){if(!r||!c||r>1000||c>1000)throw Error("Invalid matrix dimensions");}
double& Matrix::at(std::size_t r,std::size_t c){if(r>=rows_||c>=cols_)throw Error("Matrix index out of range");return data_[r*cols_+c];}
double Matrix::at(std::size_t r,std::size_t c)const{if(r>=rows_||c>=cols_)throw Error("Matrix index out of range");return data_[r*cols_+c];}
Result<Matrix> Matrix::multiply(const Matrix& b)const{if(cols_!=b.rows_)return Result<Matrix>::failure("Matrix dimensions do not conform");Matrix o(rows_,b.cols_);for(std::size_t i=0;i<rows_;++i)for(std::size_t k=0;k<cols_;++k)for(std::size_t j=0;j<b.cols_;++j)o.at(i,j)+=at(i,k)*b.at(k,j);return Result<Matrix>::success(std::move(o));}
Result<double> Matrix::determinant()const{
 if(rows_!=cols_)return Result<double>::failure("Determinant requires a square matrix");Matrix a=*this;double d=1;
 for(std::size_t i=0;i<rows_;++i){std::size_t p=i;for(std::size_t r=i+1;r<rows_;++r)if(std::abs(a.at(r,i))>std::abs(a.at(p,i)))p=r;if(std::abs(a.at(p,i))<1e-12)return Result<double>::success(0);if(p!=i){for(std::size_t c=0;c<cols_;++c)std::swap(a.at(i,c),a.at(p,c));d=-d;}double pivot=a.at(i,i);d*=pivot;for(std::size_t r=i+1;r<rows_;++r){double f=a.at(r,i)/pivot;for(std::size_t c=i+1;c<cols_;++c)a.at(r,c)-=f*a.at(i,c);}}
 return Result<double>::success(d);
}
}
