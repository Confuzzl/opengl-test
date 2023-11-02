export module world.collision.feature.edge;

import world.collision.feature.feature;
import util.polyhedron;

export class Vertex;
export class Face;
export class EdgeRegion;

export class Edge : public Feature {
  SPtr<EdgeRegion> region;

  SPtr<Vertex> tail, head;
  SPtr<Face> left, right;

public:
  Edge(Collider &parent, const unsigned short ID, SPtr<Vertex> &tail,
       SPtr<Vertex> &head);
  ~Edge();

  void setNeighbors(SPtr<Face> &left, SPtr<Face> &right);

  Vec3 getProperDirectionFrom(const Face &face) const;

  SPtr<Vertex> getTail();
  SPtr<Vertex> getHead();

  Vec3 evalAt(double l) const;

  operator Vec3() const;
};