#include <array>
#include <format>
#include <print>
#include <span>
#include <string>
#include <tuple>

using std::string, std::print;

template <typename T>
void pspan(std::span<T> s) {
  print("{} size:{}\n", s, s.size());
}

int main() {
  {
    int ca[]{1, 2, 3, 4, 4, 6, 89};
    std::span<int> cb{ca};
    pspan<int>(ca);
    pspan(cb);

    print("{} {} {}\n", cb.empty(), cb[3], cb.size_bytes());
  }

  {
    int nums[]{1, 2, 3, 4, 5};
    auto [a, b, c, d, e] = nums;
    auto x = {e, b, c, d};
    print("{}\n", x);
  }

  {
    std::tuple<int, double, string> nums{1, 2.7, "blah"};
    auto [a, b, c] = nums;
    print("{} {} {}\n", a, b, c);
  }

  {
    std::array<int, 5> nums{1, 2, 3, 4, 9};
    auto& [a, b, c, d, e] = nums;
    c = 47;
    print("{}\n", nums);
  }

  {
    struct div_res {
      long quo, rem;
    };

    auto int_div = [](const long& num, const long& denom) {
      struct div_res r{};
      r.quo = num / denom;
      r.rem = num % denom;
      return r;
    };
    auto [q, r] = int_div(47, 5);
    print("{} {}\n", q, r);
  }
}
