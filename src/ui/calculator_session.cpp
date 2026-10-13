#include "ti84/ui/calculator_session.hpp"
namespace ti84::ui {
void CalculatorSession::appendInput(std::string_view s){if(input_.size()+s.size()>4096)throw Error("Input limit exceeded");input_.append(s);}
void CalculatorSession::backspace(){if(!input_.empty())input_.pop_back();}
Result<double> CalculatorSession::evaluateInput(){auto r=calculator_.calculate(input_);if(r){history_.push_back(input_+" = "+std::to_string(r.value));if(history_.size()>500)history_.erase(history_.begin());}return r;}
Result<GraphSeries> CalculatorSession::graphInput(GraphWindow w)const{GraphEngine g;return g.sample(input_,w,calculator_.variables());}
}
