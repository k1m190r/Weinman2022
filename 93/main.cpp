#include <algorithm>
#include <functional>
#include <iostream>
#include <print>
#include <string>
#include <type_traits>
#include <vector>

using std::print, std::vector, std::string;
namespace R = std::ranges;
using namespace std::string_literals;

template <typename T>
const char* f(const T a) {
  std::cout << a;
  return typeid(T).name();
}

template <typename T>
auto value_of(const T v) {
  if constexpr (std::is_pointer_v<T>)
    return *v;
  else
    return v;
}

template <typename T>
void quick_delete(T& v, size_t idx) {
  if (idx < v.size()) {
    v[idx] = std::move(v.back());
    v.pop_back();
  }
}

int main() {
  {
    const string a = "Jimi Something";
    if (auto pos{a.find("Jimi")}; pos != string::npos)
      print("yes\n");
    else
      print("no\n");
  }

  {
    print("{}\n", f(47));
    print("{}\n", f(47L));
    print("{}\n", f("47"s));
  }
  {
    int x{47};
    int* y{&x};
    print("x: {}\n", value_of(x));
    print("y: {}\n", value_of(y));
  }
  {
    vector v{1, 23, 4, 6, 3, 29, 8, 12};
    std::erase(v, 4);
    std::erase_if(v, [](auto x) { return x % 2 == 1; });
    print("{}\n", v);
  }
  {
    vector v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print("{}\n", v);
    quick_delete(v, 3);
    quick_delete(v, 6);
    print("{}\n", v);
  }

  {
    vector v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto s = R::fold_left(v, 0, std::plus{});

    print("sum: {}\n", s);
  }
}
