#include "ti84/program/basic_runtime.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>
namespace ti84 {
namespace {std::string trim(std::string s){auto a=s.find_first_not_of(" \t\r");if(a==s.npos)return {};return s.substr(a,s.find_last_not_of(" \t\r")-a+1);}bool starts(const std::string&s,const std::string&p){return s.size()>=p.size()&&std::equal(p.begin(),p.end(),s.begin(),[](char a,char b){return std::toupper(static_cast<unsigned char>(a))==std::toupper(static_cast<unsigned char>(b));});}}
Result<ProgramOutput> BasicRuntime::run(const std::string& source,Calculator& c,std::size_t limit)const{
 std::istringstream in(source);std::string line;ProgramOutput out;std::size_t n=0;
 while(std::getline(in,line)){if(++n>limit)return Result<ProgramOutput>::failure("Program line limit exceeded");line=trim(line);if(line.empty()||line[0]=='\'')continue;
  if(starts(line,"PRINT ")){auto r=c.calculate(trim(line.substr(6)));if(!r)return Result<ProgramOutput>::failure("Line "+std::to_string(n)+": "+r.error);out.lines.push_back(std::to_string(r.value));}
  else if(starts(line,"LET ")){auto rest=trim(line.substr(4));auto p=rest.find('=');if(p==rest.npos)return Result<ProgramOutput>::failure("Line "+std::to_string(n)+": LET requires '='");auto name=trim(rest.substr(0,p));if(name.empty())return Result<ProgramOutput>::failure("Missing variable name");auto r=c.calculate(trim(rest.substr(p+1)));if(!r)return Result<ProgramOutput>::failure("Line "+std::to_string(n)+": "+r.error);c.setVariable(name,r.value);}
  else return Result<ProgramOutput>::failure("Line "+std::to_string(n)+": unsupported statement");
 }
 return Result<ProgramOutput>::success(std::move(out));
}
}
