module world.transform.transformable;

const Transformable Transformable::NO_PARENT{};

Transformable::Transformable(const Transformable *parent) : parent{parent} {}

Mat4 Transformable::getTransform() const {
  return parent->getTransform() * Translatable::transform *
         Rotatable::transform;
}