module world.collision.feature.face;

import world.collision.collider;
import world.collision.feature.vertex;
import world.collision.feature.edge;
import world.collision.vclip.region.face_region;
import util.debug;

Face::Face(const Collider &parent, const unsigned short ID,
           const unsigned short edgeCount)
    : Feature(parent, ID) {
  edges.reserve(edgeCount);
}
Face::~Face() = default;

void Face::addEdge(const Edge &edge) { edges.emplace_back(std::cref(edge)); }
void Face::finishCreation() {
  normal =
      glm::normalize(glm::cross(edges[0].get().getProperDirectionFrom(*this),
                                edges[1].get().getProperDirectionFrom(*this)));

  if (glm::all(glm::isnan(normal)))
    throw DegenerateFaceNormalException{
        "FACE NORMAL EVALUATED TO NAN VECTOR\n"};
  if (normal == ZERO)
    throw DegenerateFaceNormalException{"FACE NORMAL EVALUATED TO 0 VECTOR\n"};

  region = std::make_unique<FaceRegion>(*this);
}

Vec3 Face::getNormal() const { return normal; }
const RefVector<const Edge> &Face::getEdges() const { return edges; }
const Vertex &Face::getSampleVertex() const { return edges[0].get().getTail(); }

Collision::VClip::DPrimeState Face::signDPrime(const Edge &e,
                                               const float l) const {
  return Collision::VClip::DPrimeState::ZERO;
}