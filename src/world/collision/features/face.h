#pragma once
class Edge;
#include "feature.h"
#include "util/memory_utils.h"
#include "util/vector_utils.h"

class Face : public Feature {
  Vector<SPtr<Edge>> edges;
  Vec3 normal{};

public:
  Face(Polyhedron &parent, const unsigned short ID,
       const unsigned short edgeCount);
  void addEdge(SPtr<Edge> &edge);
  void finishCreation();
};