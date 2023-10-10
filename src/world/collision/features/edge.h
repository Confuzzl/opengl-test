#pragma once
class Face;
class Vertex;
#include "feature.h"
#include "util/memory_utils.h"
#include "util/vector_utils.h"

class Edge : public Feature {
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