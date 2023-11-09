module world.collision.feature.edge;

import world.collision.collider;
import world.collision.feature.vertex;
import world.collision.feature.face;
import world.collision.vclip.region.edge_region;
import util.debug;

Edge::Edge(const Collider &parent, const unsigned short ID, const Vertex &tail,
           const Vertex &head)
    : Feature(parent, ID), tail{tail}, head{head} {
  // std::cout << std::format("CREATING tail {} count: {} head {} count: {}\n",
  //                          (*tail).ID, tail.use_count(), (*head).ID,
  //                          head.use_count());
}
Edge::~Edge() = default;

void Edge::setNeighbors(const Face *left, const Face *right) {
  this->left = left;
  this->right = right;
}
void Edge::finishCreation() { region = std::make_unique<EdgeRegion>(*this); }

Vec3 Edge::getProperDirectionFrom(const Face &face) const {
  if (face == *left)
    return +static_cast<Vec3>(*this);
  if (face == *right)
    return -static_cast<Vec3>(*this);
  throw InvalidGetProperDirectionFromArgumentException{
      std::format("FACE {} IS NEITHER A LEFT OR RIGHT FACE OF THIS EDGE {}\n",
                  face.ID, ID)};
}

const Vertex &Edge::getTail() const { return tail; }
const Vertex &Edge::getHead() const { return head; }
const Face &Edge::getLeft() const { return *left; }
const Face &Edge::getRight() const { return *right; }

Vec3 Edge::evalAt(const float l) const {
  return tail.asGlobalCoordinate() + static_cast<Vec3>(*this) * l;
}

Edge::operator Vec3() const {
  return head.asGlobalCoordinate() - tail.asGlobalCoordinate();
}