export module util.glm;

export import <glm/glm.hpp>;
export import <glm/gtc/matrix_transform.hpp>;
export import <glm/gtc/type_ptr.hpp>;
export import <glm/gtx/string_cast.hpp>;
export import <glm/gtx/matrix_interpolation.hpp>;

export using Vec2 = glm::vec2;
export using Vec3 = glm::vec3;
export using Vec4 = glm::vec4;
export using Mat3 = glm::mat3;
export using Mat4 = glm::mat4;
export using Quat = glm::quat;

export namespace glm_util {
const Vec3 ZERO{0, 0, 0}, X{1, 0, 0}, Y{0, 1, 0}, Z{0, 0, 1};
const glm::lowp_u16vec2 QUAD_UVS[2][3]{{{0, 0}, {1, 0}, {1, 1}},
                                       {{0, 0}, {1, 1}, {0, 1}}};

Vec3 rotateAroundAxis(const Vec3 &v, const Vec3 &axis, const float deg);

Vec3 transformVector(const Vec3 &v, const Mat4 &t);
Vec3 translateVector(const Vec3 &v, const Mat4 &t);
Vec3 rotateVector(const Vec3 &v, const Mat4 &t);

Vec3 getScale(const Mat4 &m);

Mat4 matrixFrom(const Vec3 &v);
Mat4 matrixFrom(const Vec3 &axis, const float deg);
Mat4 matrixFrom(const Vec3 &v, const Vec3 &axis, const float deg);
Mat4 lerpMatrix(const Mat4 &m1, const Mat4 &m2, const double t);
}; // namespace glm_util
