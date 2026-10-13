#include "ti84/math/statistics.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
namespace ti84 {
Result<SummaryStats> summarize(std::vector<double> v){
 if(v.empty())return Result<SummaryStats>::failure("Statistics require at least one value");
 if(!std::all_of(v.begin(),v.end(),[](double x){return std::isfinite(x);}))return Result<SummaryStats>::failure("Data must be finite");
 std::sort(v.begin(),v.end());double mean=std::accumulate(v.begin(),v.end(),0.0)/static_cast<double>(v.size()),sq=0;for(double x:v)sq+=(x-mean)*(x-mean);
 double med=v.size()%2?v[v.size()/2]:(v[v.size()/2-1]+v[v.size()/2])/2;
 return Result<SummaryStats>::success({static_cast<double>(v.size()),mean,med,v.front(),v.back(),v.size()>1?std::sqrt(sq/static_cast<double>(v.size()-1)):0});
}
Result<std::pair<double,double>> linearRegression(const std::vector<double>& x,const std::vector<double>& y){
 if(x.size()!=y.size()||x.size()<2)return Result<std::pair<double,double>>::failure("Regression needs equally sized lists with at least two points");
 double mx=std::accumulate(x.begin(),x.end(),0.0)/x.size(),my=std::accumulate(y.begin(),y.end(),0.0)/y.size(),n=0,d=0;
 for(std::size_t i=0;i<x.size();++i){n+=(x[i]-mx)*(y[i]-my);d+=(x[i]-mx)*(x[i]-mx);}
 if(std::abs(d)<1e-12)return Result<std::pair<double,double>>::failure("Regression x values have zero variance");double m=n/d;return Result<std::pair<double,double>>::success({m,my-m*mx});
}
}
