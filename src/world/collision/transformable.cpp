#include "transformable.h"
mat4 Transformable::getTransform() const { return pos * rot; }
vec3 Transformable::getPosition() const { return pos[3]; }
vec3 Transformable::getForward() const { return forward; }
vec3 Transformable::getUp() const { return up; }
vec3 Transformable::getRight() const { return right; }

void Transformable::setPosition(const vec3 v) { translate(v - getPosition()); }
void Transformable::translate(const vec3 v) { pos = glm::translate(pos, v); }

void Transformable::rotate(const vec3 axis, const float deg) {
  rot = glm::rotate(rot, glm::radians(deg), axis);
  forward = rotateAroundAxis(forward, axis, deg);
  up = rotateAroundAxis(up, axis, deg);
  right = rotateAroundAxis(right, axis, deg);
}
void Transformable::resetRotate() { rot = mat4{1.0f}; }

void Transformable::rotateX(const float deg) { rotate(X_PLUS, deg); }
void Transformable::rotateY(const float deg) { rotate(Y_PLUS, deg); }
void Transformable::rotateZ(const float deg) { rotate(Z_PLUS, deg); }

void Transformable::rotateForward(const float deg) { rotate(forward, deg); }
void Transformable::rotateUp(const float deg) { rotate(up, deg); }
void Transformable::rotateRight(const float deg) { rotate(right, deg); }