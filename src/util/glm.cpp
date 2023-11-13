module util.glm;

import util.debug;

Vec3 rotateAroundAxis(const Vec3 &v, const Vec3 &axis, const float deg) {
  Vec3 norm{glm::normalize(axis)};
  float sin = std::sinf(glm::radians(deg)), cos = std::cosf(glm::radians(deg));
  return v * cos + glm::cross(norm, v) * sin +
         norm * glm::dot(norm, v) * (1 - cos);
}

Vec3 translateVector(const Vec3 &v, const Mat4 &t) {
  return Vec3{t * Vec4{v, 1}};
}
Vec3 rotateVector(const Vec3 &v, const Mat4 &t) { return Vec3{t * Vec4{v, 0}}; }

Mat4 matrixFrom(const Vec3 &v) {
  Mat4 out{1.0f};
  out = glm::translate(out, v);
  return out;
}
Mat4 matrixFrom(const Vec3 &axis, const float deg) {
  Mat4 out{1.0f};
  out = glm::rotate(out, deg, axis);
  return out;
}
Mat4 matrixFrom(const Vec3 &v, const Vec3 &axis, const float deg) {
  const Mat4 pos{matrixFrom(v)};
  const Mat4 rot{matrixFrom(axis, deg)};
  return pos * rot;
}
Mat4 lerpMatrix(const Mat4 &m1, const Mat4 &m2, const float t) {
  Mat4 out{
      glm::mat4_cast(glm::slerp(glm::quat_cast(m1), glm::quat_cast(m2), t))};
  out[3] = m1[3] * (1 - t) + m2[3] * t;
  return out;
}