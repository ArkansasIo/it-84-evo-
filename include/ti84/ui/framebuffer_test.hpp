#pragma once
#include "ti84/ui/display.hpp"
namespace ti84::ui {
inline bool framebufferSmokeTest() {
 Display d(4,3);
 d.clear({1,2,3,255});
 d.putPixel(2,1,{7,8,9,255});
 return d.width()==4 && d.height()==3 && d.pixel(2,1).r==7 && d.pixel(0,0).b==3;
}
}
