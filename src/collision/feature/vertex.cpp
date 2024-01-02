module collision.feature.vertex;

import collision.collider;
import collision.feature.edge;
import collision.vclip.region.vertex_region;

Vertex::Vertex(const Collider &parent, const unsigned short GLid, const Vec3 &pos)
    : Feature(parent, GLid), localCoordinate{pos} {}
Vertex::~Vertex() = default;

void Vertex::addNeighbor(const Edge &neighbor) {
  neighbors.emplace_back(std::cref(neighbor));
}
void Vertex::finishCreation() {
  region = std::make_unique<VertexRegion>(*this);
}

const RefVector<const Edge> &Vertex::getNeighbors() const { return neighbors; }

Collision::VClip::DPrimeState Vertex::signDPrime(const Edge &e,
                                                 const float l) const {
  const Vec3 el{e.evalAt(l)};
  if (el == asGlobalCoordinate())
    return Collision::VClip::DPrimeState::DEGENERATE;
  double s = glm::dot(static_cast<Vec3>(e), el - asGlobalCoordinate());
  if (s > 0)
    return Collision::VClip::DPrimeState::POSITIVE;
  if (s < 0)
    return Collision::VClip::DPrimeState::NEGATIVE;
  return Collision::VClip::DPrimeState::ZERO;
}

// const Vec3 &Vertex::getLocalCoordinate() const { return localCoordinate; }
Vec3 Vertex::asGlobalCoordinate() const {
  return localCoordinate + parent.getPosition();
}