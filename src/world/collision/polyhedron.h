#pragma once
class Vertex;
class Edge;
class Face;

#include "world/base_polyhedron.h"
#include <stdexcept>

class Polyhedron : public BasePolyhedron {
  struct FeatureRelatedException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  using EdgeNeighborList = Vector<glm::u8vec2>;
  using FaceEdgeIndexList = Vector2D<unsigned char>;

  Vector<Vertex> vertices;

  Vector<Edge> edges;
  EdgeNeighborList edgeVertexIndices; // edges store max 256 vertices
  EdgeNeighborList edgeFaceIndices;   // edges store max 256 faces

  Vector<Face> faces;
  FaceEdgeIndexList faceEdgeIndices; // faces store max 256 edges

public:
  Polyhedron(const Vec3List &coordinates,
             const EdgeNeighborList &edgeVertexIndice,
             const EdgeNeighborList &edgeFaceIndices,
             const FaceEdgeIndexList &faceEdgeIndices);
  ~Polyhedron();

protected:
  void createFeatures();
  void setupNeighbors();

  consteval virtual unsigned short triCount() = 0;
};