export module world.transform.rotatable;

import util.glm;

export class Rotatable {
protected:
  Mat4 transform{1.0f};
  Vec3 forward{glm_util::X_PLUS}, up{glm_util::Y_PLUS}, right{glm_util::Z_PLUS};

public:
  Mat4 getRotation() const;
  Vec3 getForward() const;
  Vec3 getUp() const;
  Vec3 getRight() const;

  void resetRotation();
  void setRotation(const Vec3 &axis, const float deg);
  void rotate(const Vec3 &axis, const float deg);
  void rotateForward(const float deg);
  void rotateUp(const float deg);
  void rotateRight(const float deg);
};