export module world.collision.features.vertex;

import world.collision.features.differentiable_feature;
import world.collision.features.feature;
import util.polyhedron;

export class Edge;

export class Vertex : public Feature, DifferentiableFeature {
  SPtrVector<Edge> neighbors;
  Vec3 localCoordinate;

public:
  Vertex(Collider &parent, const unsigned short ID, const Vec3 &pos);

  void addNeighbor(SPtr<Edge> &neighbor);

  Collision::VClip::DPrimeState signDPrime(const Edge &e, double l) override;

  operator Vec3() const;
};