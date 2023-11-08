module;

#include <typeinfo>

module world.collision.feature.feature;

import world.collision.collider;
import util.debug;

Feature::Feature(const Collider &parent, unsigned short ID)
    : parent{parent}, ID{ID} {};

bool Feature::operator==(const Feature &other) const {
  return typeid(*this) == typeid(other) and
         this->parent.ID == other.parent.ID and this->ID == other.ID;
}