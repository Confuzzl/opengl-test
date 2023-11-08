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

void Face::addEdge(const Edge &edge) { edges.emplace_back(std::cref(edge)); }
void Face::finishCreation() {
  // normal = glm::normalize(glm::cross(edges[0]->getProperDirectionFrom(*this),
  //                                    edges[1]->getProperDirectionFrom(*this)));
  normal =
      glm::normalize(glm::cross(edges[0].get().getProperDirectionFrom(*this),
                                edges[1].get().getProperDirectionFrom(*this)));
  region = std::make_unique<FaceRegion>(*this);
  // std::cout << std::format("normal: {}\n", glm::to_string(normal));
}

Vec3 Face::getNormal() const { return normal; }
const RefVector<const Edge> &Face::getEdges() const { return edges; }
const Vertex &Face::getSampleVertex() const { return edges[0].get().getTail(); }

Collision::VClip::DPrimeState Face::signDPrime(const Edge &e,
                                               const float l) const {
  return Collision::VClip::DPrimeState::ZERO;
}