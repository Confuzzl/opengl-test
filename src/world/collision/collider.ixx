export module world.collision.collider;

import world.base_polyhedron;
import util.polyhedron;
import <stdexcept>;

export class Vertex;
export class Edge;
export class Face;

export class Collider : public BasePolyhedron {
  struct FeatureRelatedException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  UPtrVector<Vertex> vertices;
  const VEIndexList &vertexEdgeIndices; // only 256 indices for edges

  UPtrVector<Edge> edges;
  const EVIndexList &edgeVertexIndices; // only 256 indices for vertices
  const EFIndexList &edgeFaceIndices;   // only 256 indices for faces

  UPtrVector<Face> faces;
  const FEIndexList &faceEdgeIndices; // only 256 indices for edges

  Vertex &addVertex(UPtr<Vertex> &&v);
  Edge &addEdge(UPtr<Edge> &&e);
  Face &addFace(UPtr<Face> &&f);

public:
  static unsigned int count;
  unsigned int ID;

  Collider(const unsigned short vertexCount, const unsigned short faceCount,
           const Vec3List &coordinates, const VEIndexList &vertexEdgeIndices,
           const EVIndexList &edgeVertexIndices,
           const EFIndexList &edgeFaceIndices,
           const FEIndexList &faceEdgeIndices);
  ~Collider();

protected:
  void createFeatures();
  void setupNeighbors();
};

export using CollPtr = UPtr<Collider>;