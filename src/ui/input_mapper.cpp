#include "ti84/ui/input_mapper.hpp"
namespace ti84::ui {
KeyAction mapKeyToAction(Key k) noexcept {
 switch(k){
 case Key::Digit0:return {"0"};case Key::Digit1:return {"1"};case Key::Digit2:return {"2"};case Key::Digit3:return {"3"};case Key::Digit4:return {"4"};case Key::Digit5:return {"5"};case Key::Digit6:return {"6"};case Key::Digit7:return {"7"};case Key::Digit8:return {"8"};case Key::Digit9:return {"9"};
 case Key::Add:return {"+"};case Key::Subtract:return {"-"};case Key::Multiply:return {"*"};case Key::Divide:return {"/"};case Key::Power:return {"^"};case Key::Decimal:return {"."};case Key::LeftParen:return {"("};case Key::RightParen:return {")"};case Key::Comma:return {","};case Key::Enter:return {{},false,false,true};case Key::Clear:return {{},true,false,false};case Key::Delete:return {{},false,true,false};
 case Key::Sin:return {"sin("};case Key::Cos:return {"cos("};case Key::Tan:return {"tan("};case Key::Sqrt:return {"sqrt("};case Key::Log:return {"log("};case Key::Ln:return {"ln("};default:return {};
 }
}
}
