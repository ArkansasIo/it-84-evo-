#include "ti84/core/expression.hpp"
#include <cmath>
#include <cctype>
#include <numbers>
namespace ti84 {
namespace {
class Parser {
 const std::string_view s_; const Variables& vars_;
 const std::unordered_map<std::string,Expression::Function>& funcs_; std::size_t p_{0};
 [[noreturn]] void fail(std::string m) const { throw Error(m); }
 void ws(){ while(p_<s_.size() && std::isspace(static_cast<unsigned char>(s_[p_]))) ++p_; }
 bool eat(char c){ ws(); if(p_<s_.size()&&s_[p_]==c){++p_;return true;}return false; }
 std::string ident(){ws();auto b=p_;while(p_<s_.size()&&(std::isalnum(static_cast<unsigned char>(s_[p_]))||s_[p_]=='_'))++p_;return std::string(s_.substr(b,p_-b));}
 double expr(){double x=term();for(;;){if(eat('+'))x+=term();else if(eat('-'))x-=term();else return x;}}
 double term(){double x=unary();for(;;){if(eat('*'))x*=unary();else if(eat('/')){double d=unary();if(d==0)fail("Division by zero");x/=d;}else if(eat('%')){double d=unary();if(d==0)fail("Modulo by zero");x=std::fmod(x,d);}else return x;}}
 double unary(){if(eat('+'))return unary();if(eat('-'))return -unary();return power();}
 double power(){double x=primary();if(eat('^'))x=std::pow(x,unary());return x;}
 double primary(){
  ws(); if(eat('(')){double x=expr();if(!eat(')'))fail("Expected ')'");return x;}
  if(p_<s_.size()&&(std::isdigit(static_cast<unsigned char>(s_[p_]))||s_[p_]=='.')){
   auto b=p_;while(p_<s_.size()&&(std::isdigit(static_cast<unsigned char>(s_[p_]))||s_[p_]=='.'))++p_;
   if(p_<s_.size()&&(s_[p_]=='e'||s_[p_]=='E')){++p_;if(p_<s_.size()&&(s_[p_]=='+'||s_[p_]=='-'))++p_;while(p_<s_.size()&&std::isdigit(static_cast<unsigned char>(s_[p_])))++p_;}
   try{return std::stod(std::string(s_.substr(b,p_-b)));}catch(...){fail("Invalid number");}
  }
  auto n=ident();if(n.empty())fail("Expected number, variable, or '('");
  if(n=="pi"||n=="PI")return std::numbers::pi;if(n=="e")return std::numbers::e;
  if(eat('(')){double a=expr();if(!eat(')'))fail("Expected ')' after function argument");auto i=funcs_.find(n);if(i==funcs_.end())fail("Unknown function: "+n);try{return i->second(a);}catch(...){fail("Function domain error: "+n);}}
  auto i=vars_.find(n);if(i==vars_.end())fail("Unknown variable: "+n);return i->second;
 }
public:
 Parser(std::string_view s,const Variables& v,const std::unordered_map<std::string,Expression::Function>& f):s_(s),vars_(v),funcs_(f){}
 double parse(){double x=expr();ws();if(p_!=s_.size())fail("Unexpected token at position "+std::to_string(p_));if(!std::isfinite(x))fail("Result is not finite");return x;}
};
}
Expression::Expression():functions_{
 {"sin",[](double x){return std::sin(x);}},{"cos",[](double x){return std::cos(x);}},
 {"tan",[](double x){return std::tan(x);}},{"asin",[](double x){return std::asin(x);}},
 {"acos",[](double x){return std::acos(x);}},{"atan",[](double x){return std::atan(x);}},
 {"sqrt",[](double x){if(x<0)throw Error("domain");return std::sqrt(x);}},
 {"abs",[](double x){return std::abs(x);}},
 {"ln",[](double x){if(x<=0)throw Error("domain");return std::log(x);}},
 {"log",[](double x){if(x<=0)throw Error("domain");return std::log10(x);}},
 {"exp",[](double x){return std::exp(x);}},{"floor",[](double x){return std::floor(x);}},
 {"ceil",[](double x){return std::ceil(x);}}
}{}
Result<double> Expression::evaluate(std::string_view s,const Variables& v) const {
 try{if(s.empty())return Result<double>::failure("Expression is empty");return Result<double>::success(Parser(s,v,functions_).parse());}
 catch(const std::exception& e){return Result<double>::failure(e.what());}
}
}
