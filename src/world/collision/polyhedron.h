#pragma once
class Vertex;
class Edge;
class Face;

#include "world/base_polyhedron.h"
#include <stdexcept>

class Polyhedron : public BasePolyhedron {
  struct VerticesSizeException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
  struct FeatureRelatedException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

private:
  SPtrVector<Vertex> vertices;
  const VertexNeighborList &vertexEdgeIndices; // only 256 indices for edges

  SPtrVector<Edge> edges;
  const EdgeNeighborList &edgeVertexIndices; // only 256 indices for vertices
  const EdgeNeighborList &edgeFaceIndices;   // only 256 indices for faces

  SPtrVector<Face> faces;
  const FaceNeighborList &faceEdgeIndices; // only 256 indices for edges

  SPtr<Vertex> &addVertex(SPtr<Vertex> &&v);
  SPtr<Edge> &addEdge(SPtr<Edge> &&e);
  SPtr<Face> &addFace(SPtr<Face> &&f);

public:
  static unsigned int count;
  unsigned int ID;

  Polyhedron(const unsigned short vertexCount, const Vec3List &coordinates,
             const VertexNeighborList &vertexEdgeIndices,
             const EdgeNeighborList &edgeVertexIndices,
             const EdgeNeighborList &edgeFaceIndices,
             const FaceNeighborList &faceEdgeIndices);
  ~Polyhedron();

protected:
  void createFeatures();
  void setupNeighbors();
};