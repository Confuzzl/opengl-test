export module world.transform.transformable;

import world.transform.translatable;
import world.transform.rotatable;
import util.glm;

export class Transformable : public Translatable, public Rotatable {
public:
  static const Transformable NO_PARENT;

  const Transformable *parent{&NO_PARENT};

  Transformable() = default;
  Transformable(const Transformable *parent);

  Mat4 getTransform() const;
};