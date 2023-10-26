export module world.collision.features.edge;

import world.collision.features.feature;
import util.polyhedron;

export class Vertex;
export class Face;

export class Edge : public Feature {
  SPtr<Vertex> tail, head;
  SPtr<Face> left, right;

public:
  Edge(Collider &parent, const unsigned short ID, SPtr<Vertex> &tail,
       SPtr<Vertex> &head);

  void setNeighbors(SPtr<Face> &left, SPtr<Face> &right);

  Vec3 getProperDirectionFrom(const Face &face);

  Vec3 evalAt(double l);

  operator Vec3() const;
};