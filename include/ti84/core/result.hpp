#pragma once
#include <stdexcept>
#include <string>
#include <utility>
namespace ti84 {
struct Error : std::runtime_error { using std::runtime_error::runtime_error; };
template<class T> struct Result {
  T value{};
  std::string error;
  explicit operator bool() const noexcept { return error.empty(); }
  static Result success(T v) { return Result{std::move(v), {}}; }
  static Result failure(std::string message) { return Result{T{}, std::move(message)}; }
};
}
