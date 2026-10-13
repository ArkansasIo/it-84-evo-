#pragma once
#include <string>
#include <vector>
#include "ti84/core/calculator.hpp"
#include "ti84/graph/graph.hpp"
#include "ti84/ui/menu.hpp"
namespace ti84::ui {
enum class Screen { Home, Graph, Table, Settings, ProgramEditor, Help };
class CalculatorSession {
public:
 Screen screen()const noexcept{return screen_;}
 void setScreen(Screen s)noexcept{screen_=s;}
 Calculator& calculator()noexcept{return calculator_;}
 const std::string& input()const noexcept{return input_;}
 void appendInput(std::string_view text);
 void backspace();
 void clearInput()noexcept{input_.clear();}
 Result<double> evaluateInput();
 Result<GraphSeries> graphInput(GraphWindow window={})const;
 const std::vector<std::string>& history()const noexcept{return history_;}
private:Screen screen_{Screen::Home};Calculator calculator_;std::string input_;std::vector<std::string> history_;
};
}
