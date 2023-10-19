export module util.vector;

import <vector>;
import <array>;

export template <typename T> using Vector = std::vector<T>;
export template <typename T> using Vector2D = std::vector<std::vector<T>>;
export template <typename T, size_t n> using Array = std::array<T, n>;