#include "ti84/graph/graph.hpp"
#include <cmath>
namespace ti84 {
Result<GraphSeries> GraphEngine::sample(std::string source,GraphWindow w,const Variables& vars)const{
 if(!(w.xMin<w.xMax)||!(w.yMin<w.yMax)||w.samples<2||w.samples>1000000)return Result<GraphSeries>::failure("Invalid graph window or sample count");
 Expression e;GraphSeries s{source,{}};s.points.reserve(w.samples);double step=(w.xMax-w.xMin)/static_cast<double>(w.samples-1);
 for(std::size_t i=0;i<w.samples;++i){double x=w.xMin+step*static_cast<double>(i);auto v=vars;v["x"]=x;auto y=e.evaluate(source,v);s.points.push_back({x,y?y.value:NAN});}
 return Result<GraphSeries>::success(std::move(s));
}
}
