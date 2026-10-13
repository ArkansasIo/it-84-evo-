#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>
namespace ti84::ui {
struct Pixel { std::uint8_t r{},g{},b{},a{255}; };
class Display {
public:
 Display(int width=320,int height=240):width_(width),height_(height),pixels_(static_cast<std::size_t>(width*height)){
  if(width<=0||height<=0||width>4096||height>4096)throw std::invalid_argument("Invalid display dimensions");
 }
 int width()const noexcept{return width_;} int height()const noexcept{return height_;}
 void clear(Pixel color={255,255,255,255}){std::fill(pixels_.begin(),pixels_.end(),color);}
 void putPixel(int x,int y,Pixel color){if(x>=0&&y>=0&&x<width_&&y<height_)pixels_[static_cast<std::size_t>(y*width_+x)]=color;}
 Pixel pixel(int x,int y)const{if(x<0||y<0||x>=width_||y>=height_)throw std::out_of_range("Pixel index out of range");return pixels_[static_cast<std::size_t>(y*width_+x)];}
 const std::vector<Pixel>& framebuffer()const noexcept{return pixels_;}
private:int width_,height_;std::vector<Pixel> pixels_;
};
}
