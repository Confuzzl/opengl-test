export module world.collision.feature.face;

import world.collision.feature.differentiable_feature;
import world.collision.feature.feature;
import util.memory;
import util.glm;
import world.collision.algorithms;
import <stdexcept>;

export class Collider;
export class Vertex;
export class Edge;
export class FaceRegion;

export class Face : public Feature, DifferentiableFeature {
  struct DegenerateFaceNormalException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  UPtr<FaceRegion> region;

  RefVector<const Edge> edges;
  Vec3 normal{};

public:
  Face(const Collider &parent, const unsigned short ID,
       const unsigned short edgeCount);
  ~Face();

  // void addEdge(const SPtr<Edge> &edge);
  void addEdge(const Edge &edge);
  void finishCreation() override;

  Vec3 getNormal() const;
  const RefVector<const Edge> &getEdges() const;
  const Vertex &getSampleVertex() const;

  Collision::VClip::DPrimeState signDPrime(const Edge &e,
                                           const float l) const override;
};