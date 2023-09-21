#pragma once
#include "util/glm_utils.h"
class Transformable {
public:
  mat4 getTransform();
  vec3 getPosition();
  vec3 getForward();
  vec3 getUp();
  vec3 getRight();

  virtual void setPosition(const vec3 v);
  virtual void translate(const vec3 v);

  virtual void rotate(const vec3 axis, const float deg);
  virtual void resetRotate();

  virtual void rotateX(const float deg);
  virtual void rotateY(const float deg);
  virtual void rotateZ(const float deg);

  virtual void rotateForward(const float deg);
  virtual void rotateUp(const float deg);
  virtual void rotateRight(const float deg);

protected:
  mat4 rot{1.0f};
  mat4 pos{1.0f};
  vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
};