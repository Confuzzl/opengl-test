#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;

inline Vec3 X_PLUS{1, 0, 0}, Y_PLUS{0, 1, 0}, Z_PLUS{0, 0, 1};
inline const glm::lowp_u16vec2 quadUV[2][3]{{{0, 0}, {1, 0}, {1, 1}},
                                            {{0, 0}, {1, 1}, {0, 1}}};

Vec3 rotateAroundAxis(Vec3 v, Vec3 axis, float deg);