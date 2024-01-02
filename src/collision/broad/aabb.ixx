export module collision.aabb;

import util.glm;
import util.math;

import <functional>;

export namespace Collision {
struct AABB {
  enum struct State {
    CLEAR,
    INTERSECTING,
    TOUCHING,
  };
  Vec3 min, max;

  Vec3 size() const { return max - min; }

  State check(const Vec3 &point) const {
    if (math_util::hadamard_in_range<std::less, std::less>(min, point, max, 3))
      return State::INTERSECTING;
    if (math_util::hadamard_in_range<std::less_equal, std::less_equal>(
            min, point, max, 3))
      return State::TOUCHING;
    return State::CLEAR;
  }

  State check(const AABB &other) const {
    if (math_util::hadamard_compare<std::less>(min, other.max, 3) &&
        math_util::hadamard_compare<std::greater>(max, other.min, 3))
      return State::INTERSECTING;
    if (math_util::hadamard_compare<std::less_equal>(min, other.max, 3) &&
        math_util::hadamard_compare<std::greater_equal>(max, other.min, 3))
      return State::TOUCHING;
    return State::CLEAR;
  }
};
} // namespace Collision