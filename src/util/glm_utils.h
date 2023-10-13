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

extern const Vec3 X_PLUS, Y_PLUS, Z_PLUS;
extern const glm::lowp_u16vec2 quadUV[2][3];

Vec3 rotateAroundAxis(const Vec3 &v, const Vec3 &axis, const float deg);