#pragma once
#include <vector>
#include <utility>
#include "ti84/core/result.hpp"
namespace ti84 {
struct SummaryStats{double count{},mean{},median{},minimum{},maximum{},sampleStdDev{};};
Result<SummaryStats> summarize(std::vector<double> values);
Result<std::pair<double,double>> linearRegression(const std::vector<double>& x,const std::vector<double>& y);
}
