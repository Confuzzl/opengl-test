module world.transform.rotatable;

Mat4 Rotatable::getRotation() const { return transform; }
Vec3 Rotatable::getForward() const { return forward; }
Vec3 Rotatable::getUp() const { return up; }
Vec3 Rotatable::getRight() const { return right; }

void Rotatable::resetRotation() { transform = Mat4{1.0f}; }
void Rotatable::setRotation(const Vec3 &axis, const float deg) {
  transform = glm::rotate(Mat4{1.0f}, glm::radians(deg), axis);
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