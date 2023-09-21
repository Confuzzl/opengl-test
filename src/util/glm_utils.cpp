#include "glm_utils.h"
vec3 rotateAroundAxis(const vec3 v, const vec3 axis, const float deg) {
  vec3 norm{glm::normalize(axis)};
  float sin = std::sinf(glm::radians(deg)), cos = std::cosf(glm::radians(deg));
  return v * cos + glm::cross(norm, v) * sin +
         norm * (glm::dot(norm, v)) * (1 - cos);
}