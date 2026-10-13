#pragma once
#include "ti84/ui/keypad.hpp"
#include <string_view>
namespace ti84::ui {
struct KeyAction { std::string_view insertion; bool clearInput{false}; bool backspace{false}; bool evaluate{false}; };
KeyAction mapKeyToAction(Key key) noexcept;
}
