#pragma once
class Vertex;
class Edge;
class Face;

#include "world/base_polyhedron.h"
#include <memory>
#include <vector>

class Polyhedron : public BasePolyhedron {
  std::vector<std::shared_ptr<Vertex>> vertices;
  std::vector<std::shared_ptr<Edge>> edges;
  std::vector<glm::u8vec2> edgeFaceIndices;
  std::vector<std::shared_ptr<Face>> faces;
  std::vector<std::vector<unsigned char>> faceEdgeIndices;

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