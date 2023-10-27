export module world.collision.feature.vertex;

import world.collision.feature.differentiable_feature;
import world.collision.feature.feature;
import util.polyhedron;

export class Edge;
export class VertexRegion;

export class Vertex : public Feature, DifferentiableFeature {
  SPtr<VertexRegion> region;

  SPtrVector<Edge> neighbors;
  Vec3 localCoordinate;

public:
  Vertex(Collider &parent, const unsigned short ID, const Vec3 &pos);
  ~Vertex();

  void addNeighbor(SPtr<Edge> &neighbor);

  Collision::VClip::DPrimeState signDPrime(const Edge &e,
                                           double l) const override;

  const Vec3 &getLocalCoordinate() const;
  Vec3 asGlobalCoordinate() const;
};