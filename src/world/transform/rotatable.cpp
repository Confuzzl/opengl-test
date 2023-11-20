module world.transform.rotatable;

Mat4 Rotatable::getRotation() const { return transform; }
Vec3 Rotatable::getForward() const { return forward; }
Vec3 Rotatable::getUp() const { return up; }
Vec3 Rotatable::getRight() const { return right; }
Vec3 Rotatable::getForwardFlat() const {
  return glm::normalize(Vec3{forward[0], 0, forward[2]});
};

void Rotatable::resetRotation() {
  transform = Mat4{1.0f};
  forward = glm_util::X;
  up = glm_util::Y;
  right = glm_util::Z;
}
void Rotatable::setRotation(const Vec3 &axis, const float deg) {
  resetRotation();
  rotate(axis, deg);
}
void Rotatable::rotate(const Vec3 &axis, const float deg) {
  transform = glm::rotate(transform, glm::radians(deg), axis);
  forward = glm_util::rotateVector(forward, transform);
  up = glm_util::rotateVector(up, transform);
  right = glm_util::rotateVector(right, transform);
}

void Rotatable::rotateForward(const float deg) { rotate(forward, deg); }
void Rotatable::rotateUp(const float deg) { rotate(up, deg); }
void Rotatable::rotateRight(const float deg) { rotate(right, deg); }