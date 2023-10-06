#pragma once
#include "polyhedron.h"

class Simplex : public Polyhedron {
  const static VertexNeighborList veIndices;
  const static EdgeNeighborList evIndices;
  const static EdgeNeighborList efIndices;
  const static FaceEdgeIndexList feIndices;

public:
  Simplex(const Vec3List &coordinates);
};