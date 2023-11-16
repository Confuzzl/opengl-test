module world.transform.transformable;

Mat4 Transformable::getTransform() const {
  return Translatable::transform * Rotatable::transform;
}