export module world.transform.transformable;

import world.transform.translatable;
import world.transform.rotatable;
import util.glm;
import util.memory;
import <optional>;

export class Transformable : public Translatable, public Rotatable {
public:
  std::optional<Ref<Transformable>> parent{std::nullopt};

  Mat4 getTransform() const;
};