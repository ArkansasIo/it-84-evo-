#pragma once
#include <string>
#include <vector>
#include "ti84/core/expression.hpp"
namespace ti84 {
struct Point{double x;double y;};
struct GraphWindow{double xMin{-10},xMax{10},yMin{-10},yMax{10};std::size_t samples{401};};
struct GraphSeries{std::string expression;std::vector<Point> points;};
class GraphEngine{public:Result<GraphSeries> sample(std::string source,GraphWindow w,const Variables& vars={})const;};
}
