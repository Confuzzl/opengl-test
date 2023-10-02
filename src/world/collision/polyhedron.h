#pragma once
#include "features/edge.h"
#include "features/face.h"
#include "features/vertex.h"
#include "transformable.h"
#include <vector>

// template <typename T>
// concept IsPolyhedron = requires(T t) { t.createFeatures(); };

// template <typename Derived, std::size_t TVertices, std::size_t TEdges,
// std::size_t TFaces>
class Polyhedron : public Transformable {
  const std::vector<vec3> coordinates;
  // std::vector<std::unique_ptr<Vertex>> vertices;
  // std::vector<std::unique_ptr<Edge>> edges;
  // std::vector<std::unique_ptr<Face>> faces;

  Polyhedron(const std::vector<vec3> &coordinates);

  // protected:
  //   virtual void createFeatures(vec3 (&coordinates)[TVertices]) = 0;
};
