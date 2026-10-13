#pragma once
#include <string>
#include "ti84/core/expression.hpp"
namespace ti84 {
enum class AngleMode { Radians, Degrees };
struct CalculatorSettings { AngleMode angleMode{AngleMode::Radians}; int decimalPlaces{8}; };
class Calculator {
public:
 Result<double> calculate(const std::string& text);
 void setVariable(std::string name,double value);
 void clearVariables() noexcept { variables_.clear(); }
 const Variables& variables() const noexcept{return variables_;}
 CalculatorSettings& settings() noexcept{return settings_;}
private:
 Expression evaluator_; Variables variables_; CalculatorSettings settings_;
};
}
