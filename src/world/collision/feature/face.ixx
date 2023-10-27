export module world.collision.feature.face;

import world.collision.feature.feature;
import util.polyhedron;

export class Edge;

export class Face : public Feature {
  SPtrVector<Edge> edges;
  Vec3 normal{};

public:
  Face(Collider &parent, const unsigned short ID,
       const unsigned short edgeCount);
  void addEdge(SPtr<Edge> &edge);
  void finishCreation();
};