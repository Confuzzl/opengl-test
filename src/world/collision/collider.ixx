export module world.collision.polyhedron;

import world.base_polyhedron;
import util.polyhedron;
import <stdexcept>;

class Vertex;
class Edge;
class Face;

export class Collider : public BasePolyhedron {
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

  Collider(const unsigned short vertexCount, const unsigned short faceCount,
           const Vec3List &coordinates,
           const VertexNeighborList &vertexEdgeIndices,
           const EdgeNeighborList &edgeVertexIndices,
           const EdgeNeighborList &edgeFaceIndices,
           const FaceNeighborList &faceEdgeIndices);

protected:
  void createFeatures();
  void setupNeighbors();
};