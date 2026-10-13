#include "ti84/math/numerical.hpp"
#include "ti84/math/matrix_ops.hpp"
#include "ti84/ui/menu.hpp"
#include "ti84/ui/calculator_session.hpp"
#include "ti84/ui/display.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#define CHECK(x) do{if(!(x))throw std::runtime_error("CHECK failed: " #x);}while(false)
int main(){try{
 auto d=ti84::derivative([](double x){return x*x;},3);CHECK(d&&std::abs(d.value-6)<1e-5);
 auto i=ti84::integrateSimpson([](double x){return x*x;},0,3,100);CHECK(i&&std::abs(i.value-9)<1e-9);
 auto root=ti84::solveBisection([](double x){return x*x-2;},0,2);CHECK(root&&std::abs(root.value-std::sqrt(2.0))<1e-8);
 ti84::Matrix m(2,2);m.at(0,0)=4;m.at(0,1)=7;m.at(1,0)=2;m.at(1,1)=6;auto inv=ti84::inverse(m);CHECK(inv&&std::abs(inv.value.at(0,0)-0.6)<1e-9);
 auto t=ti84::transpose(m);CHECK(t&&t.value.at(0,1)==2);
 ti84::ui::Menu menu("test");menu.setItems({{"one","1",true},{"disabled","x",false},{"two","2",true}});menu.move(1);CHECK(menu.selected()&&menu.selected()->label=="two");
 ti84::ui::CalculatorSession session;session.appendInput("2+2");auto r=session.evaluateInput();CHECK(r&&r.value==4&&session.history().size()==1);
 ti84::ui::Display display(4,4);display.putPixel(1,1,{10,20,30,255});CHECK(display.pixel(1,1).g==20);
 std::cout<<"UI/math extension tests passed.\n";return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
