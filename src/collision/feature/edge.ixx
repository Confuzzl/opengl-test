export module collision.feature.edge;

import collision.feature.feature;
import util.memory;
import util.glm;
import <stdexcept>;

export class Collider;
export class Vertex;
export class Face;
export class EdgeRegion;

export class Edge : public Feature {
  struct InvalidGetProperDirectionFromArgumentException
      : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
  struct DegenerateEdgeException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  UPtr<EdgeRegion> region;

  const Vertex &tail, &head;
  const Face *left, *right;

public:
  Edge(const Collider &parent, const unsigned short ID, const Vertex &tail,
       const Vertex &head);
  ~Edge();

  void setNeighbors(const Face *left, const Face *right);
  void finishCreation() override;

  Vec3 getProperDirectionFrom(const Face &face) const;

  const Vertex &getTail() const;
  const Vertex &getHead() const;
  const Face &getLeft() const;
  const Face &getRight() const;

  Vec3 evalAt(const float l) const;

  operator Vec3() const;
};