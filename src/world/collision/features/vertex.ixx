export module world.collision.features.vertex;

import world.collision.features.feature;
import util.polyhedron;

export class Edge;

export class Vertex : public Feature {
  SPtrVector<Edge> neighbors;
  Vec3 localCoordinate;

public:
  Vertex(Collider &parent, const unsigned short ID, const Vec3 &pos);

  void addNeighbor(SPtr<Edge> &neighbor);

  operator Vec3() const;
};