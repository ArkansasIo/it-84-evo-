#include "ti84/ui/graph_renderer.hpp"
#include <cmath>
#include <algorithm>
namespace ti84::ui {
void GraphRenderer::line(Display& d,int x0,int y0,int x1,int y1,Pixel c){
 int dx=std::abs(x1-x0),sx=x0<x1?1:-1,dy=-std::abs(y1-y0),sy=y0<y1?1:-1,err=dx+dy;
 for(;;){d.putPixel(x0,y0,c);if(x0==x1&&y0==y1)break;int e2=2*err;if(e2>=dy){err+=dy;x0+=sx;}if(e2<=dx){err+=dx;y0+=sy;}}
}
void GraphRenderer::render(Display& d,const GraphSeries& s,const GraphWindow& w,GraphStyle style)const{
 d.clear(style.background);const int width=d.width(),height=d.height();if(width<2||height<2||!(w.xMin<w.xMax)||!(w.yMin<w.yMax))return;
 auto px=[&](double x){return static_cast<int>(std::lround((x-w.xMin)/(w.xMax-w.xMin)*(width-1)));};
 auto py=[&](double y){return static_cast<int>(std::lround((w.yMax-y)/(w.yMax-w.yMin)*(height-1)));};
 // Grid intervals use a readable approximate 10-division grid.
 for(int i=1;i<10;++i){int x=i*(width-1)/10,y=i*(height-1)/10;line(d,x,0,x,height-1,style.grid);line(d,0,y,width-1,y,style.grid);}
 if(w.xMin<=0&&w.xMax>=0){int x=px(0);line(d,x,0,x,height-1,style.axes);}
 if(w.yMin<=0&&w.yMax>=0){int y=py(0);line(d,0,y,width-1,y,style.axes);}
 bool hasPrevious=false;int lastX=0,lastY=0;
 for(const auto& p:s.points){if(!std::isfinite(p.x)||!std::isfinite(p.y)||p.y<w.yMin-10*(w.yMax-w.yMin)||p.y>w.yMax+10*(w.yMax-w.yMin)){hasPrevious=false;continue;}
  int x=px(p.x),y=py(p.y);if(hasPrevious&&std::abs(y-lastY)<height*8)line(d,lastX,lastY,x,y,style.curve);
  lastX=x;lastY=y;hasPrevious=true;
 }
}
}
