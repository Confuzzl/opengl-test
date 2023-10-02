#pragma once
//#include "features/feature.h"
//#include "features/edge.h"
//#include "features/face.h"
//#include "features/vertex.h"
class Vertex;
class Edge;
class Face;

#include "transformable.h"
#include <memory>
#include <vector>

// template <typename T>
// concept IsPolyhedron = requires(T t) { t.createFeatures(); };

class Polyhedron : public Transformable {
  const std::vector<vec3> coordinates;
   std::vector<std::unique_ptr<Vertex>> vertices;
   std::vector<std::unique_ptr<Edge>> edges;
   std::vector<std::unique_ptr<Face>> faces;

  Polyhedron(const std::vector<vec3> &coordinates);
   ~Polyhedron();
};
