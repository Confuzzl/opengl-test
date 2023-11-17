export module util.vector;

import <vector>;
import <array>;

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
} // namespace vector_util