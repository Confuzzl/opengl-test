#pragma once
#include "transformable.h"

template <std::size_t TVertices, std::size_t TEdges, std::size_t TFaces>
class Polyhedron : public Transformable {
  vec3 coordinates[];
  vec3 vertices[];

protected:
  virtual void createFeatures(vec3 (&coordinates)[TVertices]) = 0;
};

template <typename T>
concept IsPolyhedron = requires(T t) { t.createFeatures(); };