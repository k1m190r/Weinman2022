#include <algorithm>
#include <print>
#include <ranges>
#include <string>
#include <vector>
#include <version>

using std::vector, std::string, std::print;

namespace V = std::ranges::views;
namespace R = std::ranges;

struct Particle {
  string name;
  double mass;
};

template <>
struct std::formatter<vector<Particle>> {
  template <typename PC>
  constexpr auto parse(PC& ctx) {
    return ctx.begin();
  }

  template <typename FC>
  auto format(const vector<Particle>& ps, FC& ctx) const {
    string ss{};
    for (auto p : ps) ss.append(std::format("{} {}\n", p.name, p.mass));
    return format_to(ctx.out(), "{}", ss);
  }
};

auto even = [](auto const& i) { return 0 == i % 2; };
auto x2 = [](auto const& i) { return i * 2; };

int main() {
  vector nums{11, 12, 3, 4, 5, 6, 7, 8, 9, 110};
  auto x = nums | V::reverse | V::take(7) | V::filter(even) | V::transform(x2);

  vector v = vector(x.begin(), x.end());
  R::sort(v);

  print("x:{} v:{}\n", x, v);

  vector<Particle> particles{
      {"Electron", 0.511}, {"Muon", 105.66},   {"Tau", 1776.86},
      {"Positron", 0.511}, {"Proton", 938.27}, {"Neutron", 939.57},
  };

  R::sort(particles, {}, &Particle::name);
  print("Sort by name:\n{}\n", particles);

  R::sort(particles, {}, &Particle::mass);
  print("Sort by mass:\n{}\n", particles);
}
