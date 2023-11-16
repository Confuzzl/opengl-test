module world.transform.rotatable;

Mat4 Rotatable::getRotation() const { return transform; }
Vec3 Rotatable::getRelativeX() const { return rX; }
Vec3 Rotatable::getRelativeY() const { return rY; }
Vec3 Rotatable::getRelativeZ() const { return rZ; }

void Rotatable::resetRotation() { transform = Mat4{1.0f}; }
void Rotatable::setRotation(const Vec3 &axis, const float deg) {
  transform = glm::rotate(Mat4{1.0f}, glm::radians(deg), axis);
}
void Rotatable::rotate(const Vec3 &axis, const float deg) {
  transform = glm::rotate(transform, glm::radians(deg), axis);
}

void Rotatable::rotateRX(const float deg) { rotate(rX, deg); }
void Rotatable::rotateRY(const float deg) { rotate(rY, deg); }
void Rotatable::rotateRZ(const float deg) { rotate(rZ, deg); }