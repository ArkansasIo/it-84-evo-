#include "ti84/core/calculator.hpp"
namespace ti84 {
Result<double> Calculator::calculate(const std::string& s){return evaluator_.evaluate(s,variables_);}
void Calculator::setVariable(std::string n,double v){if(n.empty())throw Error("Variable name cannot be empty");variables_[std::move(n)]=v;}
}
