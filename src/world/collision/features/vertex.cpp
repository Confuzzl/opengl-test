#include "vertex.h"
#include "edge.h"

Vertex::Vertex(Polyhedron &parent, const unsigned short ID, const vec3 pos)
    : Feature(parent, ID), localCoordinate{pos} {}
Vertex::~Vertex() = default;

Vertex::operator vec3() const { return {localCoordinate}; }