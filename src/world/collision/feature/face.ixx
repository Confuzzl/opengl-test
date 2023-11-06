export module world.collision.feature.face;

import world.collision.feature.differentiable_feature;
import world.collision.feature.feature;
import util.polyhedron;

export class Edge;
export class FaceRegion;

export class Face : public Feature, DifferentiableFeature {
  UPtr<FaceRegion> region;

  SPtrVector<Edge> edges;
  Vec3 normal{};

public:
  Face(Collider &parent, const unsigned short ID,
       const unsigned short edgeCount);
  ~Face();

  void addEdge(const SPtr<Edge> &edge);
  void finishCreation();

  Vec3 getNormal() const;
  const SPtrVector<Edge> &getEdges() const;

  Collision::VClip::DPrimeState signDPrime(const Edge &e,
                                           float l) const override;
};