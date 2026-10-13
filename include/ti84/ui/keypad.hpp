#pragma once
#include <array>
#include <string_view>
#include <optional>
namespace ti84::ui {
enum class Key {
 None, Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7,Digit8,Digit9,
 Add,Subtract,Multiply,Divide,Power,Decimal,LeftParen,RightParen,Comma,
 Enter,Clear,Delete,Negate,Sin,Cos,Tan,Sqrt,Log,Ln,Graph,Window,Zoom,Trace,
 Up,Down,Left,Right,Mode,Vars,Matrix,Stat,Alpha,Second
};
struct KeyDefinition { Key key; std::string_view label; };
class Keypad {
public:
 static constexpr std::array<KeyDefinition,42> layout{{
  {Key::Second,"2nd"},{Key::Mode,"MODE"},{Key::Delete,"DEL"},{Key::Clear,"CLEAR"},
  {Key::Left,"◀"},{Key::Up,"▲"},{Key::Down,"▼"},{Key::Right,"▶"},
  {Key::Graph,"GRAPH"},{Key::Window,"WINDOW"},{Key::Zoom,"ZOOM"},{Key::Trace,"TRACE"},
  {Key::Sin,"SIN"},{Key::Cos,"COS"},{Key::Tan,"TAN"},{Key::Power,"^"},
  {Key::Log,"LOG"},{Key::Ln,"LN"},{Key::Sqrt,"√"},{Key::LeftParen,"("},
  {Key::RightParen,")"},{Key::Comma,","},{Key::Matrix,"MATRIX"},{Key::Vars,"VARS"},
  {Key::Digit7,"7"},{Key::Digit8,"8"},{Key::Digit9,"9"},{Key::Divide,"÷"},
  {Key::Digit4,"4"},{Key::Digit5,"5"},{Key::Digit6,"6"},{Key::Multiply,"×"},
  {Key::Digit1,"1"},{Key::Digit2,"2"},{Key::Digit3,"3"},{Key::Subtract,"−"},
  {Key::Digit0,"0"},{Key::Decimal,"."},{Key::Negate,"(-)"},{Key::Add,"+"},
  {Key::Stat,"STAT"},{Key::Enter,"ENTER"}
 }};
};
}
