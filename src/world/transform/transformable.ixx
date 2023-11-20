export module world.transform.transformable;

import world.transform.translatable;
import world.transform.rotatable;
import util.glm;
import <optional>;

export class Transformable : public Translatable, public Rotatable {
public:
  Mat4 getTransform() const;
};