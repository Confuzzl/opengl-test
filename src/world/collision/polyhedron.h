#pragma once
class Vertex;
class Edge;
class Face;

#include "util/memory_utils.h"
#include "world/base_polyhedron.h"
#include <stdexcept>

class Polyhedron : public BasePolyhedron {
  struct FeatureRelatedException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  template <typename T> using SPtrVector = Vector<SPtr<T>>;
  using VertexNeighborList = Vector<glm::u8vec2>;
  using EdgeNeighborList = Vector<glm::u8vec2>;
  using FaceEdgeIndexList = Vector2D<unsigned char>;

  SPtrVector<Vertex> vertices;
  VertexNeighborList vertexEdgeIndices; // only 256 indices for edges

  SPtrVector<Edge> edges;
  EdgeNeighborList edgeVertexIndices; // only 256 indices for vertices
  EdgeNeighborList edgeFaceIndices;   // only 256 indices for faces

  SPtrVector<Face> faces;
  FaceEdgeIndexList faceEdgeIndices; // only 256 indices for edges

  SPtr<Vertex> &addVertex(SPtr<Vertex> &&v);
  SPtr<Edge> &addEdge(SPtr<Edge> &&e);
  SPtr<Face> &addFace(SPtr<Face> &&f);

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