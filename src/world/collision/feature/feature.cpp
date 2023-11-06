module;

#include <typeinfo>

module world.collision.feature.feature;

Feature::Feature(Collider &parent, unsigned short ID)
    : parent{parent}, ID{ID} {};

bool Feature::operator==(const Feature &other) const {
  return typeid(this) == typeid(other) and parent.ID == other.parent.ID and
         ID == other.ID;
}