export module world.collision.feature.edge;

import world.collision.feature.feature;
import util.memory;
import util.glm;

export class Collider;
export class Vertex;
export class Face;
export class EdgeRegion;

export class Edge : public Feature {
  UPtr<EdgeRegion> region;

  const Vertex &tail, &head;
  const Face *left, *right;

public:
  Edge(const Collider &parent, const unsigned short ID, const Vertex &tail,
       const Vertex &head);
  ~Edge();

  void setNeighbors(Face *left, Face *right);
  void finishCreation() override;

  Vec3 getProperDirectionFrom(const Face &face) const;

  const Vertex &getTail() const;
  const Vertex &getHead() const;
  const Face &getLeft() const;
  const Face &getRight() const;

  Vec3 evalAt(const float l) const;

  operator Vec3() const;
};