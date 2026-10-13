#include "ti84/core/calculator.hpp"
#include "ti84/graph/graph.hpp"
#include "ti84/math/matrix.hpp"
#include "ti84/math/statistics.hpp"
#include "ti84/storage/memory_store.hpp"
#include "ti84/program/basic_runtime.hpp"
#include <cmath>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#define CHECK(x) do{if(!(x))throw std::runtime_error("CHECK failed: " #x);}while(false)
int main(){try{
 ti84::Calculator c;auto a=c.calculate("2+3*4");CHECK(a&&std::abs(a.value-14)<1e-9);
 auto b=c.calculate("2^3^2");CHECK(b&&std::abs(b.value-512)<1e-9);
 auto d=c.calculate("sqrt(81)+sin(pi/2)");CHECK(d&&std::abs(d.value-10)<1e-9);CHECK(!c.calculate("1/0"));
 c.setVariable("A",7);auto e=c.calculate("A*2");CHECK(e&&e.value==14);
 ti84::GraphEngine g;auto s=g.sample("x^2",{-2,2,-1,5,5});CHECK(s&&s.value.points.size()==5);CHECK(std::abs(s.value.points[2].y)<1e-9);
 ti84::Matrix m(2,2);m.at(0,0)=1;m.at(0,1)=2;m.at(1,0)=3;m.at(1,1)=4;auto det=m.determinant();CHECK(det&&std::abs(det.value+2)<1e-9);
 auto st=ti84::summarize({1,2,3,4,5});CHECK(st&&st.value.mean==3&&st.value.median==3);
 auto lr=ti84::linearRegression({1,2,3},{3,5,7});CHECK(lr&&std::abs(lr.value.first-2)<1e-9&&std::abs(lr.value.second-1)<1e-9);
 ti84::MemoryStore store;store.set("A","12.5");auto p=std::filesystem::temp_directory_path()/"ti84evo-test.mem";CHECK(store.save(p));ti84::MemoryStore loaded;CHECK(loaded.load(p));CHECK(loaded.get("A")=="12.5");std::filesystem::remove(p);
 ti84::BasicRuntime rt;auto pr=rt.run("LET A = 9\nPRINT A*2",c);CHECK(pr&&pr.value.lines.size()==1&&std::stod(pr.value.lines[0])==18);
 std::cout<<"All tests passed.\n";return 0;
 }catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
