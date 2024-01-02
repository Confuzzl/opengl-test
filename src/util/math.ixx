export module util.math;

import <random>;

export namespace math_util {
std::random_device rd;
std::mt19937 mt{rd()};

template <typename T>
concept subscriptable = requires(T t) { t[0]; };

double random(const double min, const double max) {
  return std::uniform_real_distribution<double>{min, max}(mt);
}

template <template <typename> typename comparator, subscriptable T>
bool hadamard_compare(T a, T b, unsigned int range) {
  bool out = true;
  const comparator<decltype(std::declval<T>().operator[](0))> compare{};
  for (unsigned int i = 0; i < range; i++)
    out &= compare(a[i], b[i]);
  return out;
}

template <template <typename> typename lower,
          template <typename> typename upper, subscriptable T>
bool hadamard_in_range(T min, T n, T max, unsigned int range) {
  return hadamard_compare<lower, T>(min, n, range) &&
         hadamard_compare<upper, T>(n, max, range);
}
} // namespace math_util
