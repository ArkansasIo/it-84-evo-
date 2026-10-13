#include "ti84/ui/menu.hpp"
#include <utility>
namespace ti84::ui {
Menu::Menu(std::string t):title_(std::move(t)){}
void Menu::setItems(std::vector<MenuItem> v){items_=std::move(v);selected_=0;normalize();}
void Menu::normalize(){if(items_.empty()){selected_=0;return;}if(selected_>=items_.size())selected_=items_.size()-1;if(!items_[selected_].enabled)move(1);}
void Menu::move(int delta){if(items_.empty()||delta==0)return;for(std::size_t i=0;i<items_.size();++i){selected_=static_cast<std::size_t>((static_cast<long long>(selected_)+delta+static_cast<long long>(items_.size()))%static_cast<long long>(items_.size()));if(items_[selected_].enabled)return;}}
const MenuItem* Menu::selected()const noexcept{return items_.empty()||!items_[selected_].enabled?nullptr:&items_[selected_];}
}
