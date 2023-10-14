export module world.collision.features.face;

import world.collision.features.feature;
import util.polyhedron;

export class Edge;

export class Face : public Feature {
  SPtrVector<Edge> edges;
  Vec3 normal{};

public:
  Face(Polyhedron &parent, const unsigned short ID,
       const unsigned short edgeCount);
  void addEdge(SPtr<Edge> &edge);
  void finishCreation();
};