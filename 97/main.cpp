// safe comparison of integers of different types
// <utility> cmp_equal _not_equal _less _less_equal _greater _greater_equal

// spaceship <=> === [-1 0 +1]

#include <print>    // format print
#include <utility>  // cmp_less

using std::print, std::string;

int main() {
  // safe integer comparisons
  {
    int x{-3};
    unsigned y{7};
    if (std::cmp_less(x, y))
      print("true\n");
    else
      print("false\n");
  }
  {
    auto a = 7;
    auto b = 42;
    auto c = a <=> b;
    print("{} <=> {} → {} {} {}\n", a, b, c == 0, c < 0, c > 0);
  }
}
