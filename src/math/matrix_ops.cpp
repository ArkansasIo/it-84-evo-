#include "ti84/math/matrix_ops.hpp"
#include <cmath>
#include <algorithm>
namespace ti84 {
Result<Matrix> transpose(const Matrix& a){Matrix out(a.cols(),a.rows());for(std::size_t r=0;r<a.rows();++r)for(std::size_t c=0;c<a.cols();++c)out.at(c,r)=a.at(r,c);return Result<Matrix>::success(std::move(out));}
Result<Matrix> reducedRowEchelonForm(const Matrix& input,double eps){
 if(eps<=0)return Result<Matrix>::failure("Epsilon must be positive");Matrix a=input;std::size_t lead=0;
 for(std::size_t r=0;r<a.rows()&&lead<a.cols();++r){
  std::size_t pivot=r;for(std::size_t i=r;i<a.rows();++i)if(std::abs(a.at(i,lead))>std::abs(a.at(pivot,lead)))pivot=i;
  while(lead<a.cols()&&std::abs(a.at(pivot,lead))<=eps){++lead;if(lead>=a.cols())return Result<Matrix>::success(std::move(a));pivot=r;for(std::size_t i=r;i<a.rows();++i)if(std::abs(a.at(i,lead))>std::abs(a.at(pivot,lead)))pivot=i;}
  for(std::size_t c=0;c<a.cols();++c)std::swap(a.at(pivot,c),a.at(r,c));double d=a.at(r,lead);for(std::size_t c=0;c<a.cols();++c)a.at(r,c)/=d;
  for(std::size_t i=0;i<a.rows();++i)if(i!=r){double f=a.at(i,lead);for(std::size_t c=0;c<a.cols();++c)a.at(i,c)-=f*a.at(r,c);}
  ++lead;
 }
 for(std::size_t r=0;r<a.rows();++r)for(std::size_t c=0;c<a.cols();++c)if(std::abs(a.at(r,c))<eps)a.at(r,c)=0;
 return Result<Matrix>::success(std::move(a));
}
Result<Matrix> inverse(const Matrix& input,double eps){
 if(input.rows()!=input.cols())return Result<Matrix>::failure("Inverse requires a square matrix");
 const auto n=input.rows();Matrix aug(n,n*2);
 for(std::size_t r=0;r<n;++r)for(std::size_t c=0;c<n;++c){aug.at(r,c)=input.at(r,c);aug.at(r,c+n)=r==c?1.0:0.0;}
 for(std::size_t col=0;col<n;++col){std::size_t pivot=col;for(std::size_t r=col+1;r<n;++r)if(std::abs(aug.at(r,col))>std::abs(aug.at(pivot,col)))pivot=r;
  if(std::abs(aug.at(pivot,col))<eps)return Result<Matrix>::failure("Matrix is singular");
  for(std::size_t c=0;c<2*n;++c)std::swap(aug.at(pivot,c),aug.at(col,c));double d=aug.at(col,col);for(std::size_t c=0;c<2*n;++c)aug.at(col,c)/=d;
  for(std::size_t r=0;r<n;++r)if(r!=col){double f=aug.at(r,col);for(std::size_t c=0;c<2*n;++c)aug.at(r,c)-=f*aug.at(col,c);}
 }
 Matrix out(n,n);for(std::size_t r=0;r<n;++r)for(std::size_t c=0;c<n;++c)out.at(r,c)=aug.at(r,c+n);return Result<Matrix>::success(std::move(out));
}
}
