module world.collision.features.feature;

Feature::Feature(Collider &parent, unsigned short ID)
    : parent{parent}, ID{ID} {};

bool Feature::operator==(const Feature &other) const {
  return parent.ID == other.parent.ID and ID == other.ID;
}