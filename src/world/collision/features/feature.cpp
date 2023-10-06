#include "feature.h"

Feature::Feature(Polyhedron &parent, unsigned short ID)
    : parent{parent}, ID{ID} {};

bool Feature::operator==(const Feature &other) const {
  return parent.ID == other.parent.ID and ID == other.ID;
}