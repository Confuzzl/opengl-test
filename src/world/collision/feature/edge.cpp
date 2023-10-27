module world.collision.feature.edge;

import world.collision.feature.vertex;
import world.collision.feature.face;
import world.collision.vclip.region.regions;

Edge::Edge(Collider &parent, const unsigned short ID, SPtr<Vertex> &tail,
           SPtr<Vertex> &head)
    : Feature(parent, ID), tail{tail}, head{head} {
  // std::cout << std::format("CREATING tail {} count: {} head {} count: {}\n",
  //                          (*tail).ID, tail.use_count(), (*head).ID,
  //                          head.use_count());
}
Edge::~Edge() = default;

void Edge::setNeighbors(SPtr<Face> &left, SPtr<Face> &right) {
  this->left = left;
  this->right = right;
}

Vec3 Edge::getProperDirectionFrom(const Face &face) const {
  if (face == *left) {
    return *this;
  }
  if (face == *right) {
    return -static_cast<Vec3>(*this);
  }
  return {};
}

Vec3 Edge::evalAt(double l) const {
  return tail->asGlobalCoordinate() +
         static_cast<Vec3>(*this) * static_cast<float>(l);
}

Edge::operator Vec3() const {
  return head->getLocalCoordinate() - tail->getLocalCoordinate();
}