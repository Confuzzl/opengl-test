#pragma once
#include "feature.h"
#include "vertex.h"
#include "face.h"

class Edge : public Feature {
  Vertex& tail, &head;
  Face &cw, &ccw;

  Edge(Polyhedron &parent, const unsigned short ID, const Vertex &tail, const Vertex &head);
};