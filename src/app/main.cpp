#include "ti84/core/calculator.hpp"
#include "ti84/graph/graph.hpp"
#include "ti84/math/statistics.hpp"
#include "ti84/storage/memory_store.hpp"
#include "ti84/program/basic_runtime.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

namespace {
std::string trim(std::string s) {
 const auto first=s.find_first_not_of(" \t\r\n");
 if(first==std::string::npos)return {};
 const auto last=s.find_last_not_of(" \t\r\n");
 return s.substr(first,last-first+1);
}
}
int main(){
 ti84::Calculator calc;ti84::GraphEngine graph;ti84::MemoryStore memory;ti84::BasicRuntime basic;
 std::cout<<"TI-84 Evo-inspired Calculator (original implementation)\nType :help for commands; :quit to exit.\n";
 std::string line;
 while(std::cout<<"TI84> "&&std::getline(std::cin,line)){
  if(line==":quit"||line==":q")break;
  if(line==":help"){std::cout<<":let NAME = EXPR | :vars | :graph EXPR | :save FILE | :load FILE\n:stats 1,2,3 | :run FILE | :quit\n";continue;}
  if(line.rfind(":let ",0)==0){
   auto b=line.substr(5);auto eq=b.find('=');
   if(eq==b.npos){std::cout<<"Usage: :let NAME = EXPR\n";continue;}
   auto name=trim(b.substr(0,eq));auto r=calc.calculate(trim(b.substr(eq+1)));
   if(!r){std::cout<<"Error: "<<r.error<<'\n';continue;}
   try{calc.setVariable(name,r.value);std::cout<<name<<" = "<<r.value<<'\n';}
   catch(const std::exception&e){std::cout<<"Error: "<<e.what()<<'\n';}continue;
  }
  if(line==":vars"){for(auto&[k,v]:calc.variables())std::cout<<k<<" = "<<v<<'\n';continue;}
  if(line.rfind(":graph ",0)==0){auto r=graph.sample(line.substr(7),{});if(!r){std::cout<<r.error<<'\n';continue;}std::size_t n=0;for(auto&p:r.value.points)if(std::isfinite(p.y))++n;std::cout<<"Sampled "<<r.value.points.size()<<" points; "<<n<<" valid.\n";for(std::size_t i=0;i<r.value.points.size()&&i<8;++i)std::cout<<r.value.points[i].x<<", "<<r.value.points[i].y<<'\n';continue;}
  if(line.rfind(":save ",0)==0){
   for(const auto&[name,value]:calc.variables()){std::ostringstream out;out<<std::setprecision(17)<<value;memory.set(name,out.str());}
   auto r=memory.save(trim(line.substr(6)));std::cout<<(r?"Variables saved":r.error)<<'\n';continue;
  }
  if(line.rfind(":load ",0)==0){
   auto r=memory.load(trim(line.substr(6)));if(!r){std::cout<<"Error: "<<r.error<<'\n';continue;}
   calc.clearVariables();bool valid=true;
   try{for(const auto&name:memory.keys()){const auto value=memory.get(name);std::size_t used=0;double parsed=std::stod(value,&used);if(used!=value.size()||!std::isfinite(parsed)){valid=false;break;}calc.setVariable(name,parsed);}}
   catch(const std::exception&){valid=false;}
   if(!valid)std::cout<<"Memory file contains a non-numeric variable; some values may not have loaded.\n";else std::cout<<"Variables loaded.\n";continue;
  }
  if(line.rfind(":stats ",0)==0){std::vector<double> v;std::string s=line.substr(7);std::size_t p=0;try{while(p<s.size()){auto q=s.find(',',p);v.push_back(std::stod(s.substr(p,q==s.npos?q:q-p)));if(q==s.npos)break;p=q+1;}}catch(...){std::cout<<"Invalid list\n";continue;}auto r=ti84::summarize(v);if(!r){std::cout<<r.error<<'\n';continue;}auto a=r.value;std::cout<<"n="<<a.count<<" mean="<<a.mean<<" median="<<a.median<<" min="<<a.minimum<<" max="<<a.maximum<<" sampleSD="<<a.sampleStdDev<<'\n';continue;}
  if(line.rfind(":run ",0)==0){std::ifstream f(trim(line.substr(5)));if(!f){std::cout<<"Cannot open program file\n";continue;}std::string s((std::istreambuf_iterator<char>(f)),{});auto r=basic.run(s,calc);if(!r){std::cout<<r.error<<'\n';continue;}for(auto&v:r.value.lines)std::cout<<v<<'\n';continue;}
  auto r=calc.calculate(line);if(r)std::cout<<std::setprecision(calc.settings().decimalPlaces)<<r.value<<'\n';else std::cout<<"Error: "<<r.error<<'\n';
 }
 std::cout<<"Goodbye.\n";
}
