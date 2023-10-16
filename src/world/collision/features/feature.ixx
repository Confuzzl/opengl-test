export module world.collision.features.feature;

import world.collision.polyhedron;

export class Feature {
public:
  const Collider &parent;
  const unsigned short ID;
  bool operator==(const Feature &other) const;

protected:
  Feature(Collider &parent, const unsigned short ID);
};
