#include "ti84/math/complex.hpp"
#include "ti84/math/probability.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#define CHECK(x) do{if(!(x))throw std::runtime_error("CHECK failed: " #x);}while(false)
int main(){try{
 auto z=ti84::divide({2,4},{1,-1});CHECK(z&&std::abs(z.value.real()+1)<1e-9&&std::abs(z.value.imag()-3)<1e-9);
 CHECK(std::abs(ti84::magnitude({3,4})-5)<1e-9);CHECK(!ti84::divide({1,2},{0,0}));
 auto pdf=ti84::normalPdf(0);CHECK(pdf&&std::abs(pdf.value-0.3989422804)<1e-8);
 auto cdf=ti84::normalCdf(0);CHECK(cdf&&std::abs(cdf.value-0.5)<1e-12);
 auto pmf=ti84::binomialPmf(4,2,0.5);CHECK(pmf&&std::abs(pmf.value-0.375)<1e-12);
 std::cout<<"Probability/complex tests passed.\n";return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
