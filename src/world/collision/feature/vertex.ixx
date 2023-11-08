export module world.collision.feature.vertex;

import world.collision.feature.differentiable_feature;
import world.collision.feature.feature;
import util.memory;
import util.glm;

export class Collider;
export class Edge;
export class VertexRegion;

export class Vertex : public Feature, DifferentiableFeature {
  UPtr<VertexRegion> region;

  RefVector<const Edge> neighbors;
  Vec3 localCoordinate;

public:
  Vertex(const Collider &parent, const unsigned short ID, const Vec3 &pos);
  ~Vertex();

  void addNeighbor(const Edge &neighbor);
  void finishCreation() override;

  const RefVector<const Edge> &getNeighbors() const;

  Collision::VClip::DPrimeState signDPrime(const Edge &e,
                                           const float l) const override;

  // const Vec3 &getLocalCoordinate() const;
  Vec3 asGlobalCoordinate() const;
};
