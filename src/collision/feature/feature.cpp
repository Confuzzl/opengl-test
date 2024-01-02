module;

#include <typeinfo>

module collision.feature.feature;

import collision.collider;
import util.debug;

Feature::Feature(const Collider &parent, unsigned short ID)
    : parent{parent}, ID{ID} {};

bool Feature::operator==(const Feature &other) const {
  return typeid(*this) == typeid(other) and
         this->parent.ID == other.parent.ID and this->ID == other.ID;
}