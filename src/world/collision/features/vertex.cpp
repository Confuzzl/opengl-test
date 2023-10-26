module world.collision.features.vertex;

import world.collision.features.edge;

Vertex::Vertex(Collider &parent, const unsigned short ID, const Vec3 &pos)
    : Feature(parent, ID), localCoordinate{pos} {}

void Vertex::addNeighbor(SPtr<Edge> &neighbor) {
  neighbors.emplace_back(neighbor);
}

Collision::VClip::DPrimeState Vertex::signDPrime(const Edge &e, double l) {
  return Collision::VClip::DPrimeState::ZERO;
}

Vertex::operator Vec3() const { return localCoordinate; }