#pragma once
#include "util/glm_utils.h"
class Transformable {
public:
  Mat4 getTransform() const;
  Vec3 getPosition() const;
  Vec3 getForward() const;
  Vec3 getUp() const;
  Vec3 getRight() const;

  virtual void setPosition(const Vec3 v);
  virtual void translate(const Vec3 v);

  virtual void rotate(const Vec3 axis, const float deg);
  virtual void resetRotate();

  virtual void rotateX(const float deg);
  virtual void rotateY(const float deg);
  virtual void rotateZ(const float deg);

  virtual void rotateForward(const float deg);
  virtual void rotateUp(const float deg);
  virtual void rotateRight(const float deg);

protected:
  Mat4 rot{1.0f};
  Mat4 pos{1.0f};
  Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
};