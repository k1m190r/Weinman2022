#include <algorithm>
#include <print>
#include <ranges>
#include <string>
#include <vector>

using std::vector, std::print, std::string;
namespace R = std::ranges;
namespace V = std::ranges::views;

template <typename T>
constexpr bool is_gt_byte{sizeof(T) > 1};

template <typename T>
concept Numeric = is_gt_byte<T> && (std::integral<T> || std::floating_point<T>);

template <Numeric T>
// requires Numeric<T>
T arg42(const T &arg) {
  return arg + 42;
}

auto arg42_(Numeric auto &arg) { return arg + 42; }

template <typename T>
  requires std::floating_point<T>
T pi{3.1415926535897932385L};

template <typename T>
  requires std::integral<T>
constexpr double avg(vector<T> const &vec) {
  double sum = R::fold_left(vec, 0, std::plus<T>());
  double s = static_cast<double>(vec.size());
  return sum / s;
}

int main() {
  {  // <=> spaceshift operator
    struct Num {
      int a;
      constexpr Num(int _a) : a{_a} {}
      auto operator<=>(const Num &) const = default;
    };

    constexpr Num a{7}, b{7}, c{42};

    print("{} {} {}\n", a.a, b.a, c.a);
    print("{} {} {}\n", a < c, a == b, a <= b);
  }

  {  // template
    const char *n{"7"};
    print("n:{} arg42:{} pi:{}\n", n, arg42(8), pi<long double>);

    auto a{avg(vector{3, 4, 1})};
    print("avg: {}\n", a);
  }

  {  // ranges
    const vector nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
    // auto res = ranges::take_view(nums, 5);

    auto res = nums | V::take(5) | V::reverse |
               V::filter([](const int i) { return 0 == i % 2; }) |
               V::transform([](const int i) { return i * i; });

    print("res: {}\n", res);
  }
}
