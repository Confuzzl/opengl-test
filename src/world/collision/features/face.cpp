#include "face.h"
#include "edge.h"
#include "util/debug_utils.h"

Face::Face(Polyhedron &parent, const unsigned short ID,
           const unsigned char edgeCount)
    : Feature(parent, ID) {
  edges.reserve(edgeCount);
}

void Face::addEdge(SPtr<Edge> &edge) {
  edges.emplace_back(edge);
  std::cout << std::format("edge {} : {}\n", (*edge).ID, edge.use_count());
}
void Face::finishCreation() {
  normal = glm::normalize(glm::cross((Vec3)*edges[0], (Vec3)*edges[1]));
}