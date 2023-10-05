#pragma once
#include "util/glm_utils.h"
class Transformable {
public:
  mat4 getTransform() const;
  vec3 getPosition() const;
  vec3 getForward() const;
  vec3 getUp() const;
  vec3 getRight() const;

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