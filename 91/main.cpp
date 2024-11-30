#include <print>
#include <ranges>
#include <string>

// #include "../../AOC2023/demangle.h"

using std::string, std::print;
namespace R = std::ranges;
namespace V = std::ranges::views;
using namespace std::string_literals;

struct Day {
  size_t v{};
};

constexpr Day operator""_day(unsigned long long d) noexcept {
  return Day(static_cast<size_t>(d));
}

int main() {
  {
    string s = "124 2342"s;
    auto fn = [](auto v) { return 100 * std::stoi(string(v.begin(), v.end())); };
    auto s2 = s | V::split(' ') | V::transform(fn) | V::reverse;
    // | V::reverse | R::to<string>;
    print("\n{}\n", s2);
  }

  {
    auto d = 1923'234'3;
    print("{}", d);
  }
}
