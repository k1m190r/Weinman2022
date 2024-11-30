// using fmt to print any object

#include <print>

using std::print;
using std::string;

struct Frac {
  long n, d;
};

template <>
struct std::formatter<Frac> {
  template <typename PC>
  constexpr auto parse(PC &ctx) {
    return ctx.begin();
  };

  template <typename FC>
  auto format(const Frac &f, FC &ctx) const {
    return format_to(ctx.out(), "{0:d}/{1:d}", f.n, f.d);
  };
};

int main() {
  {
    print("set {:^10}\n", 37);
  }

  Frac f{5, 3};
  print("Frac: {}\n", f);
}
