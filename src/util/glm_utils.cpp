#include "glm_utils.h"

extern const Vec3 X_PLUS{1, 0, 0}, Y_PLUS{0, 1, 0}, Z_PLUS{0, 0, 1};
extern const glm::lowp_u16vec2 quadUV[2][3] = {{{0, 0}, {1, 0}, {1, 1}},
                                               {{0, 0}, {1, 1}, {0, 1}}};

Vec3 rotateAroundAxis(const Vec3 &v, const Vec3 &axis, const float deg) {
  Vec3 norm{glm::normalize(axis)};
  float sin = std::sinf(glm::radians(deg)), cos = std::cosf(glm::radians(deg));
  return v * cos + glm::cross(norm, v) * sin +
         norm * (glm::dot(norm, v)) * (1 - cos);
}