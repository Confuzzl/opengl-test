#include "edge.h"
#include "face.h"
#include "vertex.h"

Edge::Edge(Polyhedron &parent, const unsigned short ID, SPtr<Vertex> &tail,
           SPtr<Vertex> &head)
    : Feature(parent, ID), tail{tail}, head{head} {}
// Edge::~Edge() = default;

Edge::operator Vec3() const { return (Vec3)*head - (Vec3)*tail; }