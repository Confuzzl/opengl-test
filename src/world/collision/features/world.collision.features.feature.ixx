export module world.collision.features.feature;

import world.collision.polyhedron;

export class Feature {
public:
  const Polyhedron &parent;
  const unsigned short ID;
  bool operator==(const Feature &other) const;

protected:
  Feature(Polyhedron &parent, const unsigned short ID);
};
