export module util.math;

import <random>;

std::random_device rd;
std::mt19937 mt{rd()};

export double random(const double min, const double max) {
  return std::uniform_real_distribution<double>{min, max}(mt);
}