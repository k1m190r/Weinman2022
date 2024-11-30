#include <map>
#include <print>
#include <ranges>
#include <string>
#include <unordered_map>
#include <utility>

using std::string, std::print;

using namespace std::string_literals;

template <typename M, typename K>
bool node_swap(M& m, K k1, K k2) {
  auto n1{m.extract(k1)};
  auto n2{m.extract(k2)};
  if (n1.empty() || n2.empty()) return false;
  std::swap(n1.key(), n2.key());
  m.insert(std::move(n1));
  m.insert(std::move(n2));
  return true;
}

template <typename T>
struct Coord {
  T x{}, y{};
};

// template <typename T>
// constexpr bool operator==(const Coord<T>& lhs, const Coord<T>& rhs) {
//   return (lhs.x == rhs.x) && (lhs.y == rhs.y);
// }

// template <typename T>
// struct std::hash<Coord<T>> {
//   size_t operator()(const Coord<T>& c) const {
//     return static_cast<size_t>(c.x) + static_cast<size_t>(c.y);
//   }
// };

// template <typename T>
// struct std::formatter<Coord<T>> : formatter<string_view> {
//   auto format(Coord<T> &c, format_context& ctx) const;
// };

// template <typename T>
// auto std::formatter<Coord<T>>::format(Coord<T> &c, format_context& ctx) const {
//   auto ss = std::format("{} {}", c.x, c.y);
//   return formatter<string_view>::format(ss, ctx);
// }

template <>
struct std::formatter<Coord<int>> {
  template <typename PC>
  constexpr auto parse(PC& ctx) {
    return ctx.begin();
  }

  template <typename FC>
  auto format(const Coord<int>& ps, FC& ctx) const {
    return std::format_to(ctx.out(), "{} {}", ps.x, ps.y);
    // string ss{};
    // for (auto p : ps) ss.append(std::format("{} {}\n", p.name, p.mass));
    // return format_to(ctx.out(), "{}", ss);
  }
};

using Coordmap = std::unordered_map<Coord<int>, int>;

int main() {
  {
    std::map<string, string> m;
    m["Miles"] = "Trumpet"s;
    m.insert(std::pair<string, string>("Hendrix", "Guitar"));
    m.emplace("Krupa", "Drums");

    print("{::}\n", m);
  }

  {
    struct BigThing {
      string v_;
      BigThing(const char* v) : v_{v} { print("Constructed: {}\n", v_); }
    };

    using BigMap = std::map<string, BigThing>;

    auto print_map = [](BigMap& m) {
      print("{{");
      for (auto& [k, v] : m) {
        print("{}:{} ", k, v.v_);
      }
      print("}}\n");
    };

    BigMap m;
    m.emplace("Miles", "Trumpet");
    m.emplace("Miles", "Trumpet");
    m.try_emplace("Hendrix", "Guitar");
    auto [it, b] = m.try_emplace("Hendrix", "Guitar");
    print("a.1:{} a.2:{} b:{}\n", it->first, it->second.v_, b);

    print_map(m);
  }

  {  // efficently modify the keys of map items

    std::map<int, string> m{{1, "foo"}, {2, "bar"}, {3, "baz"}};

    print("{}\n", m);

    auto it = m.begin();
    print("it:{}\n", *it);

    // it->first = 47; // error

    // same as function node_swap

    auto n1 = m.extract(1);
    auto n2 = m.extract(2);
    std::swap(n1.key(), n2.key());
    m.insert(std::move(n1));
    m.insert(std::move(n2));

    print("{}\n", m);
  }

  {
    std::map<int, string> m{{1, "111"}};

    auto v = m[2];
    print("{}\n", m);

    auto n = m.extract(3);
    auto n2 = m.extract(2);
    print("{} \n{} {}\n", m, n.empty(), n2.empty());
  }

  {
    // BROKEN
    auto cm = Coordmap{{{3, 3}, 3}, {{2, 2}, 2}};
    // print("{}\n", cm);
  }
}
