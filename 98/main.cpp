// comptime vectors and strings with constexpr
// required g++-12 or clang 14 and pre-release version of c++ vscode extension
// consteval must be run at comptime, vs constexpr maybe at comptime or RT

#include <ctre-unicode.hpp>
#include <numeric>
#include <print>
#include <vector>
#include <string>

using std::print;
using std::string, std::vector;

consteval auto use_string() {
  string str{"string"};
  return str.size();
}

consteval auto use_vector() {
  vector<int> vec{1, 2, 3, 4, 5};
  return accumulate(begin(vec), end(vec), 0);
}

int main() {
  // auto matcher = ctre::match<"regex">;

  auto input = std::string_view{"123,456,768"};

  for (auto match : ctre::range<"([0-9]+),?">(input)) {
    print("{}\n", std::string_view{match.get<0>()});
  }

  print("{}\n", use_string());
  print("{}\n", use_vector());
  print("{}\n", vector<int>{12, 3, 3, 4});
}
