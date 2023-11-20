module world.transform.transformable;

// Transformable::Transformable(std::optional<const Transformable *> parent)
//     : parent{parent} {}

Mat4 Transformable::getTransform() const {
  return Translatable::transform * Rotatable::transform;
}