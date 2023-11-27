module world.transform.transformable;

import util.debug;

Mat4 Transformable::getTransform() const {
  return Translatable::transform * Rotatable::transform;
}