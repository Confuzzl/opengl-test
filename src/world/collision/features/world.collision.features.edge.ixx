export module world.collision.features.edge;

import world.collision.features.feature;
import util.polyhedron;

export class Vertex;
export class Face;

export class Edge : public Feature {
  SPtr<Vertex> tail, head;
  SPtr<Face> left, right;

public:
  Edge(Polyhedron &parent, const unsigned short ID, SPtr<Vertex> &tail,
       SPtr<Vertex> &head);
  //~Edge();
  void setNeighbors(SPtr<Face> &left, SPtr<Face> &right);

  Vec3 getProperDirectionFrom(const Face &face);

  operator Vec3() const;
};