export module world.transformable;

import util.glm;
import <optional>;

export class Transformable {
public:
  std::optional<Transformable *> parent{std::nullopt};

  Mat4 getTransform() const;
  Vec3 getPosition() const;
  Quat getRotation() const;
  Vec3 getForward() const;
  Vec3 getUp() const;
  Vec3 getRight() const;

  void setPosition(const Vec3 &v);
  void translate(const Vec3 &v);

  void rotate(const Vec3 &axis, const float deg);
  void resetRotate();

  void rotateX(const float deg);
  void rotateY(const float deg);
  void rotateZ(const float deg);

  void rotateForward(const float deg);
  void rotateUp(const float deg);
  void rotateRight(const float deg);

protected:
  Mat4 rot{1.0f};
  Mat4 pos{1.0f};
  Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
};