#pragma once
#include "transformable.h"
#include "features/face.h"
#include "features/edge.h"
#include "features/vertex.h"
#include <vector>

//template <typename T>
//concept IsPolyhedron = requires(T t) { t.createFeatures(); };

//template <typename Derived, std::size_t TVertices, std::size_t TEdges, std::size_t TFaces>
class Polyhedron : public Transformable {
  const std::vector<vec3> coordinates;
  const std::vector<Vertex
  Edge edges[];
  Face faces[];


  Polyhedron(const std::vector<vec3> &coordinates);

//protected:
//  virtual void createFeatures(vec3 (&coordinates)[TVertices]) = 0;
};

