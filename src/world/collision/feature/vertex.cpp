module world.collision.feature.vertex;

import world.collision.feature.edge;
import world.collision.vclip.region.regions;

Vertex::Vertex(Collider &parent, const unsigned short ID, const Vec3 &pos)
    : Feature(parent, ID), localCoordinate{pos} {}
Vertex::~Vertex() = default;

void Vertex::addNeighbor(SPtr<Edge> &neighbor) {
  neighbors.emplace_back(neighbor);
}

Collision::VClip::DPrimeState Vertex::signDPrime(const Edge &e,
                                                 double l) const {
  const Vec3 el = e.evalAt(l);
  if (el == asGlobalCoordinate())
    return Collision::VClip::DPrimeState::DEGENERATE;
  double s = glm::dot(static_cast<Vec3>(e), el - asGlobalCoordinate());
  if (s > 0)
    return Collision::VClip::DPrimeState::POSITIVE;
  if (s < 0)
    return Collision::VClip::DPrimeState::NEGATIVE;
  return Collision::VClip::DPrimeState::ZERO;
}

const Vec3 &Vertex::getLocalCoordinate() const { return localCoordinate; }
Vec3 Vertex::asGlobalCoordinate() const {
  return localCoordinate + parent.getPosition();
}