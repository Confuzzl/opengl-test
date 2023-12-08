export module util.vector;

import <vector>;
import <array>;
import <ranges>;
import <functional>;

export template <typename T> using Vector = std::vector<T>;
export template <typename T> using Vector2D = std::vector<std::vector<T>>;
export template <typename T, size_t n> using Array = std::array<T, n>;

export namespace vector_util {
template <typename T, typename... Args> Vector<T> makeVector(Args &&...args) {
  Vector<T> out;
  out.reserve(sizeof...(Args));
  (out.emplace_back(std::forward<Args>(args)), ...);
  return out;
}

template <typename T, typename F>
T fromRange(
    const std::ranges::transform_view<std::ranges::ref_view<T>, F> &range) {
  return T{range.begin(), range.end()};
}

Vector<unsigned int> range(const unsigned int a, const unsigned int b) {
  const auto iotaRange{std::ranges::views::iota(a, b)};
  return {iotaRange.begin(), iotaRange.end()};
}

template <typename In, typename Out>
Vector<Out> mapVector(const Vector<In> &in,
                      const std::function<Out(const In &)> map) {
  Vector<Out> out;
  out.reserve(in.size());
  for (const In &i : in)
    out.emplace_back(map(i));
  return out;
}

template <typename Out>
Vector<Out> mapVectorRange(const unsigned int a, const unsigned int b,
                           const std::function<Out(const unsigned int &)> map) {
  return mapVector<unsigned int, Out>(range(a, b), map);
}
} // namespace vector_util