#include "edge.h"
#include "face.h"
#include "util/debug_utils.h"
#include "vertex.h"

Edge::Edge(Polyhedron &parent, const unsigned short ID, SPtr<Vertex> &tail,
           SPtr<Vertex> &head)
    : Feature(parent, ID), tail{tail}, head{head} {
  std::cout << std::format("CREATING tail {} count: {} head {} count: {}\n",
                           (*tail).ID, tail.use_count(), (*head).ID,
                           head.use_count());
} // Edge::~Edge() = default;

Vec3 Edge::getProperDirectionFrom(const Face &face) {
  if (face == *left) {
    std::cout << "left\n";
    return *this;
  } else {
    std::cout << "right\n";
    return -(Vec3) * this;
  }
  // return face == &*left ? (Vec3) * this : -(Vec3) * this;
}

Edge::operator Vec3() const { return (Vec3)*head - (Vec3)*tail; }