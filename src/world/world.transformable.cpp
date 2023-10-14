module world.transformable;

Mat4 Transformable::getTransform() const { return pos * rot; }
Vec3 Transformable::getPosition() const { return pos[3]; }
Vec3 Transformable::getForward() const { return forward; }
Vec3 Transformable::getUp() const { return up; }
Vec3 Transformable::getRight() const { return right; }

void Transformable::setPosition(const Vec3 v) { translate(v - getPosition()); }
void Transformable::translate(const Vec3 v) { pos = glm::translate(pos, v); }

void Transformable::rotate(const Vec3 axis, const float deg) {
  rot = glm::rotate(rot, glm::radians(deg), axis);
  forward = rotateAroundAxis(forward, axis, deg);
  up = rotateAroundAxis(up, axis, deg);
  right = rotateAroundAxis(right, axis, deg);
}
void Transformable::resetRotate() { rot = Mat4{1.0f}; }

void Transformable::rotateX(const float deg) { rotate(X_PLUS, deg); }
void Transformable::rotateY(const float deg) { rotate(Y_PLUS, deg); }
void Transformable::rotateZ(const float deg) { rotate(Z_PLUS, deg); }

void Transformable::rotateForward(const float deg) { rotate(forward, deg); }
void Transformable::rotateUp(const float deg) { rotate(up, deg); }
void Transformable::rotateRight(const float deg) { rotate(right, deg); }