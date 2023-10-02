#include "edge.h"

Edge::Edge(Polyhedron &parent, const unsigned short ID, const Vertex &tail,
           const Vertex &head)
    : Feature(parent, ID), tail{tail}, head{head} {}

Edge::operator vec3() const { return (vec3)head - (vec3)tail; }