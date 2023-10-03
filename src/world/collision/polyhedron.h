#pragma once
class Vertex;
class Edge;
class Face;

#include "transformable.h"
#include "wrapper/program/vertex_formats.h"
#include <memory>
#include <vector>

// template <typename T>
// concept IsPolyhedron = requires(T p) { p.triCount(); };

class Polyhedron : public Transformable {
  const std::vector<vec3> coordinates;
  std::vector<std::shared_ptr<Vertex>> vertices;
  std::vector<std::shared_ptr<Edge>> edges;
  std::vector<std::shared_ptr<Face>> faces;

protected:
  Polyhedron(const std::vector<vec3> &coordinates);
  ~Polyhedron();

  void createFeatures();
  void setupNeighbors();

  consteval virtual unsigned short triCount() = 0;
  DefaultVertex vertexInfo[*3];
};