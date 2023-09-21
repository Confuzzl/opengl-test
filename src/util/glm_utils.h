#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;

const vec3 X_PLUS{1, 0, 0}, Y_PLUS{0, 1, 0}, Z_PLUS{0, 0, 1};
const glm::lowp_u16vec2 quadUV[2][3]{{{0, 0}, {1, 0}, {1, 1}},
                                     {{0, 0}, {1, 1}, {0, 1}}};

vec3 rotateAroundAxis(vec3 v, vec3 axis, float deg);