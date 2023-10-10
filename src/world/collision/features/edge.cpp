#include "edge.h"
#include "face.h"
#include "util/debug_utils.h"
#include "vertex.h"

Edge::Edge(Polyhedron &parent, const unsigned short ID, SPtr<Vertex> &tail,
           SPtr<Vertex> &head)
    : Feature(parent, ID), tail{tail}, head{head} {
  // std::cout << std::format("CREATING tail {} count: {} head {} count: {}\n",
  //                          (*tail).ID, tail.use_count(), (*head).ID,
  //                          head.use_count());
} // Edge::~Edge() = default;

void Edge::setNeighbors(SPtr<Face> &left, SPtr<Face> &right) {
  this->left = left;
  this->right = right;
}

Vec3 Edge::getProperDirectionFrom(const Face &face) {
  if (face == *left) {
    return *this;
  }
  if (face == *right) {
    return -(Vec3)(*this);
  }
  return {};
}

Edge::operator Vec3() const { return (Vec3)*head - (Vec3)*tail; }