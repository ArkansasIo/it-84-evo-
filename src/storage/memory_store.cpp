#include "ti84/storage/memory_store.hpp"
#include <fstream>
#include <iomanip>
#include <algorithm>
namespace ti84 {
void MemoryStore::set(std::string k,std::string v){if(k.empty())throw Error("Storage key cannot be empty");values_[std::move(k)]=std::move(v);}
bool MemoryStore::contains(const std::string& k)const{return values_.contains(k);}
std::string MemoryStore::get(const std::string& k)const{auto i=values_.find(k);if(i==values_.end())throw Error("Key not found: "+k);return i->second;}
std::vector<std::string> MemoryStore::keys()const{std::vector<std::string> o;for(auto&[k,v]:values_){(void)v;o.push_back(k);}std::sort(o.begin(),o.end());return o;}
Result<bool> MemoryStore::save(const std::filesystem::path& p)const{std::ofstream f(p,std::ios::binary|std::ios::trunc);if(!f)return Result<bool>::failure("Cannot open file for writing");f<<"TI84EVO-MEMORY-1\n"<<values_.size()<<"\n";for(auto&[k,v]:values_)f<<std::quoted(k)<<' '<<std::quoted(v)<<'\n';if(!f)return Result<bool>::failure("Failed while writing memory file");return Result<bool>::success(true);}
Result<bool> MemoryStore::load(const std::filesystem::path& p){std::ifstream f(p,std::ios::binary);if(!f)return Result<bool>::failure("Cannot open memory file");std::string magic;std::getline(f,magic);if(magic!="TI84EVO-MEMORY-1")return Result<bool>::failure("Unsupported memory file format");std::size_t n{};if(!(f>>n)||n>100000)return Result<bool>::failure("Invalid memory entry count");std::unordered_map<std::string,std::string> candidate;for(std::size_t i=0;i<n;++i){std::string k,v;if(!(f>>std::quoted(k)>>std::quoted(v))||k.empty())return Result<bool>::failure("Corrupt memory file");candidate[k]=v;}values_=std::move(candidate);return Result<bool>::success(true);}
}
