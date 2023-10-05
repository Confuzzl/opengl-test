#include "face.h"
#include "edge.h"

Face::Face(Polyhedron &parent, const unsigned short ID,
           const Vector<Edge> &edges)
    : Feature(parent, ID), edges{edges}, normal{calculateNormal()} {}
// Face::~Face() = default;

Vec3 Face::calculateNormal() {
  return glm::normalize(glm::cross((Vec3)*edges[0], (Vec3)*edges[1]));
}