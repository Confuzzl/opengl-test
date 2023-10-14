module world.collision.features.face;

import world.collision.features.edge;

Face::Face(Polyhedron &parent, const unsigned short ID,
           const unsigned short edgeCount)
    : Feature(parent, ID) {
  edges.reserve(edgeCount);
}

void Face::addEdge(SPtr<Edge> &edge) {
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