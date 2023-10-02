#include "vertex.h"

Vertex::Vertex(Polyhedron &parent, const unsigned short ID, const vec3 pos)
    : Feature(parent, ID), localCoordinate{pos} {}

Vertex::operator vec3() const { return {localCoordinate}; }