module world.collision.feature.face;

import world.collision.collider;
import world.collision.feature.vertex;
import world.collision.feature.edge;
import world.collision.vclip.region.face_region;

Face::Face(const Collider &parent, const unsigned short ID,
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
  normal = glm::normalize(glm::cross(edges[0]->getProperDirectionFrom(*this),
                                     edges[1]->getProperDirectionFrom(*this)));
  region = std::make_unique<FaceRegion>(*this);
  // std::cout << std::format("normal: {}\n", glm::to_string(normal));
}

Vec3 Face::getNormal() const { return normal; }
const SPtrVector<Edge> &Face::getEdges() const { return edges; }
const Vertex &Face::getSampleVertex() const { return edges[0]->getTail(); }

Collision::VClip::DPrimeState Face::signDPrime(const Edge &e,
                                               const float l) const {
  return Collision::VClip::DPrimeState::ZERO;
}