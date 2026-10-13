#pragma once
#include <string>
#include <vector>
#include "ti84/core/calculator.hpp"
namespace ti84 {
struct ProgramOutput{std::vector<std::string> lines;};
class BasicRuntime{public:Result<ProgramOutput> run(const std::string& source,Calculator& calculator,std::size_t maxLines=10000)const;};
}
