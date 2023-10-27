module world.collision.feature.face;

import world.collision.feature.edge;
import world.collision.vclip.region.regions;

Face::Face(Collider &parent, const unsigned short ID,
           const unsigned short edgeCount)
    : Feature(parent, ID) {
  edges.reserve(edgeCount);
}
Face::~Face() = default;

void Face::addEdge(const SPtr<Edge> &edge) {
  edges.emplace_back(edge);
  // std::cout << std::format("FACE ADDING edge {} : {}\n", (*edge).ID,
  //                          edge.use_count());
}
void Face::finishCreation() {
  normal =
      glm::normalize(glm::cross((*edges[0]).getProperDirectionFrom(*this),
                                (*edges[1]).getProperDirectionFrom(*this)));
  // std::cout << std::format("normal: {}\n", glm::to_string(normal));
}

Collision::VClip::DPrimeState Face::signDPrime(const Edge &e, double l) const {
  return Collision::VClip::DPrimeState::ZERO;
}