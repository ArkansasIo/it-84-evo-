#pragma once
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include "ti84/core/result.hpp"
namespace ti84 {
using Variables = std::unordered_map<std::string,double>;
class Expression {
public:
  using Function = std::function<double(double)>;
  Expression();
  Result<double> evaluate(std::string_view source, const Variables& vars = {}) const;
private:
  std::unordered_map<std::string,Function> functions_;
};
}
