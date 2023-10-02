#include "face.h"
#include "edge.h"

Face::Face(Polyhedron &parent, const unsigned short ID,
           const std::vector<std::unique_ptr<Edge>> &edges)
    : Feature(parent, ID), edges{edges}, normal{calculateNormal()} {}
Face::~Face() = default;

vec3 Face::calculateNormal() {
  return glm::normalize(glm::cross((vec3)*edges[0], (vec3)*edges[1]));
}