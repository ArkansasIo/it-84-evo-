#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>
#include "ti84/core/result.hpp"
namespace ti84 {
class MemoryStore{
public:void set(std::string key,std::string value);bool contains(const std::string& key)const;std::string get(const std::string& key)const;std::vector<std::string> keys()const;Result<bool> save(const std::filesystem::path& file)const;Result<bool> load(const std::filesystem::path& file);
private:std::unordered_map<std::string,std::string> values_;
};
}
