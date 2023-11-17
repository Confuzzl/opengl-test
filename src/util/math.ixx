export module util.math;

import <random>;

export namespace math_util {
std::random_device rd;
std::mt19937 mt{rd()};

double random(const double min, const double max) {
  return std::uniform_real_distribution<double>{min, max}(mt);
}
} // namespace math_util
