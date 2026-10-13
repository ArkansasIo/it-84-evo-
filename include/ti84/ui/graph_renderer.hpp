#pragma once
#include "ti84/ui/display.hpp"
#include "ti84/graph/graph.hpp"
namespace ti84::ui {
struct GraphStyle {
 Pixel background{255,255,255,255};
 Pixel grid{220,225,230,255};
 Pixel axes{50,55,60,255};
 Pixel curve{20,90,190,255};
};
class GraphRenderer {
public:
 void render(Display& display,const GraphSeries& series,const GraphWindow& window,GraphStyle style={})const;
private:
 static void line(Display& display,int x0,int y0,int x1,int y1,Pixel color);
};
}
