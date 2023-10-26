module world.collision.features.edge;

import world.collision.features.vertex;
import world.collision.features.face;

Edge::Edge(Collider &parent, const unsigned short ID, SPtr<Vertex> &tail,
           SPtr<Vertex> &head)
    : Feature(parent, ID), tail{tail}, head{head} {
  // std::cout << std::format("CREATING tail {} count: {} head {} count: {}\n",
  //                          (*tail).ID, tail.use_count(), (*head).ID,
  //                          head.use_count());
}

void Edge::setNeighbors(SPtr<Face> &left, SPtr<Face> &right) {
  this->left = left;
  this->right = right;
}

Vec3 Edge::getProperDirectionFrom(const Face &face) {
  if (face == *left) {
    return *this;
  }
  if (face == *right) {
    return -static_cast<Vec3>(*this);
  }
  return {};
}

Vec3 Edge::evalAt(double l) {
  const Vec3 temp = *this;
  temp *= l;
  return static_cast<Vec3>(*tail) + temp;
}

Edge::operator Vec3() const {
  return static_cast<Vec3>(*head) - static_cast<Vec3>(*tail);
}