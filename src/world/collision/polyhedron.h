#pragma once
class Vertex;
class Edge;
class Face;

#include "world/base_polyhedron.h"
#include <memory>
#include <vector>

class Polyhedron : public BasePolyhedron {
  Vector<Vertex> vertices;

  Vector<Edge> edges;
  Vector<glm::u8vec2> edgeFaceIndices;

  Vector<std::shared_ptr<Face>> faces;
  Vector2D<unsigned char> faceEdgeIndices;

public:
  Polyhedron(const Vec3List &coordinates);
  ~Polyhedron();

  void verifyVertices();
  void verifyEdges();
  void verifyFaces();

protected:
  void createFeatures();
  void setupNeighbors();

  consteval virtual unsigned short triCount() = 0;
};