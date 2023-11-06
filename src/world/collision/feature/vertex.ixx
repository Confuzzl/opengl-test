export module world.collision.feature.vertex;

import world.collision.feature.differentiable_feature;
import world.collision.feature.feature;
import util.polyhedron;

export class Edge;
class VertexRegion;

export class Vertex : public Feature, DifferentiableFeature {
  UPtr<VertexRegion> region;

  SPtrVector<Edge> neighbors;
  Vec3 localCoordinate;

public:
  Vertex(Collider &parent, const unsigned short ID, const Vec3 &pos);
  ~Vertex();

  void addNeighbor(SPtr<Edge> &neighbor);

  const SPtrVector<Edge> &getNeighbors() const;

  Collision::VClip::DPrimeState signDPrime(const Edge &e,
                                           float l) const override;

  const Vec3 &getLocalCoordinate() const;
  Vec3 asGlobalCoordinate() const;
};
