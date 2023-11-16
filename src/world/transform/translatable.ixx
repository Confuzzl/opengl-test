export module world.transform.translatable;

import util.glm;

export class Translatable {
protected:
  Mat4 transform{1.0f};

public:
  Vec3 getPosition() const;

  void setPosition(const Vec3 &v);
  void translate(const Vec3 &v);
};