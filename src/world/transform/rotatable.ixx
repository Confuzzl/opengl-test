export module world.transform.rotatable;

import util.glm;

export class Rotatable {
protected:
  Mat4 transform{1.0f};
  Vec3 rX{X_PLUS}, rY{Y_PLUS}, rZ{Z_PLUS};

public:
  Mat4 getRotation() const;
  Vec3 getRelativeX() const;
  Vec3 getRelativeY() const;
  Vec3 getRelativeZ() const;

  void resetRotation();
  void setRotation(const Vec3 &axis, const float deg);
  void rotate(const Vec3 &axis, const float deg);
  void rotateRX(const float deg);
  void rotateRY(const float deg);
  void rotateRZ(const float deg);
};