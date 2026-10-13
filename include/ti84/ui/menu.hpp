#pragma once
#include <string>
#include <vector>
#include <cstddef>
namespace ti84::ui {
struct MenuItem { std::string label; std::string command; bool enabled{true}; };
class Menu {
public:
 explicit Menu(std::string title={});
 void setItems(std::vector<MenuItem> items);
 const std::string& title()const noexcept{return title_;}
 const std::vector<MenuItem>& items()const noexcept{return items_;}
 std::size_t selectedIndex()const noexcept{return selected_;}
 void move(int delta);
 const MenuItem* selected()const noexcept;
private:std::string title_;std::vector<MenuItem> items_;std::size_t selected_{0};void normalize();
};
}
