module world.collision.features.vertex;

import world.collision.features.edge;

Vertex::Vertex(Collider &parent, const unsigned short ID, const Vec3 pos)
    : Feature(parent, ID), localCoordinate{pos} {}
// Vertex::~Vertex() = default;

void Vertex::addNeighbor(SPtr<Edge> &neighbor) {
  neighbors.emplace_back(neighbor);
}

Vertex::operator Vec3() const { return {localCoordinate}; }