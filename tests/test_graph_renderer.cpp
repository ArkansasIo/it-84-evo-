#include "ti84/ui/graph_renderer.hpp"
#include "ti84/ui/input_mapper.hpp"
#include <iostream>
#include <stdexcept>
#define CHECK(x) do{if(!(x))throw std::runtime_error("CHECK failed: " #x);}while(false)
int main(){try{
 ti84::ui::Display d(100,80);ti84::GraphSeries s{"x",{{-10,-10},{0,0},{10,10}}};ti84::GraphWindow w{-10,10,-10,10,3};
 ti84::ui::GraphRenderer renderer;renderer.render(d,s,w);CHECK(d.width()==100&&d.height()==80);
 auto action=ti84::ui::mapKeyToAction(ti84::ui::Key::Sin);CHECK(action.insertion=="sin(");
 auto enter=ti84::ui::mapKeyToAction(ti84::ui::Key::Enter);CHECK(enter.evaluate);
 std::cout<<"Graph renderer/input mapper tests passed.\n";return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
