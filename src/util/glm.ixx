export module util.glm;

export import <glm/glm.hpp>;
export import <glm/gtc/matrix_transform.hpp>;
export import <glm/gtc/type_ptr.hpp>;
export import <glm/gtx/string_cast.hpp>;

export using Vec2 = glm::vec2;
export using Vec3 = glm::vec3;
export using Vec4 = glm::vec4;
export using Mat3 = glm::mat3;
export using Mat4 = glm::mat4;

export constexpr Vec3 X_PLUS{1, 0, 0}, Y_PLUS{0, 1, 0}, Z_PLUS{0, 0, 1};
export constexpr glm::lowp_u16vec2 QUAD_UVS[2][3]{{{0, 0}, {1, 0}, {1, 1}},
                                                  {{0, 0}, {1, 1}, {0, 1}}};

export Vec3 rotateAroundAxis(const Vec3 &v, const Vec3 &axis, const float deg) {
  Vec3 norm{glm::normalize(axis)};
  float sin = std::sinf(glm::radians(deg)), cos = std::cosf(glm::radians(deg));
  return v * cos + glm::cross(norm, v) * sin +
         norm * (glm::dot(norm, v)) * (1 - cos);
}