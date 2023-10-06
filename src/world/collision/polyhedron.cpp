#include "polyhedron.h"
#include "features/edge.h"
#include "features/face.h"
#include "features/vertex.h"

Polyhedron::Polyhedron(const Vec3List &coordinates,
                       const EdgeNeighborList &edgeVertexIndices,
                       const EdgeNeighborList &edgeFaceIndices,
                       const FaceEdgeIndexList &faceEdgeIndices)
    : BasePolyhedron(coordinates), edgeVertexIndices{edgeVertexIndices},
      edgeFaceIndices{edgeFaceIndices}, faceEdgeIndices{faceEdgeIndices} {
  if (coordinates.size() > 256)
    throw FeatureRelatedException{
        "VERTEX COUNT OF COORDINATES EXCEEDS VERTEX INDEX RANGE (256)"};

  if (edgeVertexIndices.size() != edgeFaceIndices.size())
    throw FeatureRelatedException{
        "EDGE-VERTEX INDICES COUNT DOES NOT EQUAL EDGE-FACE INDICES COUNT"};
  if (edgeVertexIndices.size() > 256)
    throw FeatureRelatedException{
        "EDGE COUNT OF EDGE-VERTEX INDICES EXCEEDS EDGE INDEX RANGE (256)"};
  if (edgeFaceIndices.size() > 256)
    throw FeatureRelatedException{
        "EDGE COUNT OF EDGE-FACE INDICES EXCEEDS EDGE INDEX RANGE (256)"};

  if (faceEdgeIndices.size() > 256)
    throw FeatureRelatedException{
        "FACE COUNT OF FACE-EDGE INDICES EXCEEDS FACE INDEX RANGE (256)"};

  vertices.reserve(coordinates.size());
  edges.reserve(edgeVertexIndices.size());
  faces.reserve(faceEdgeIndices.size());
}
Polyhedron::~Polyhedron() = default;

SPtr<Vertex> &Polyhedron::addVertex(SPtr<Vertex> &&v) {
  return vertices.emplace_back(v);
}
SPtr<Edge> &Polyhedron::addEdge(SPtr<Edge> &&e) {
  return edges.emplace_back(e);
}
SPtr<Face> &Polyhedron::addFace(SPtr<Face> &&f) {
  return faces.emplace_back(f);
}

void Polyhedron::createFeatures() {
  for (unsigned short i = 0; const Vec3 &v : coordinates) {
    addVertex(std::make_shared<Vertex>(*this, i++, v));
  }
  for (unsigned short i = 0; const auto &pair : edgeVertexIndices) {
    unsigned char tailIndex = pair[0], headIndex = pair[1];
    addEdge(std::make_shared<Edge>(*this, i++, vertices[tailIndex],
                                   vertices[headIndex]));
  }
  for (unsigned short i = 0; const auto &face : faceEdgeIndices) {
    SPtr<Face> &f = addFace(std::make_shared<Face>(*this, i++, face.size()));
    for (const unsigned char &index : face) {
      (*f).addEdge(edges[index]);
    }
    (*f).finishCreation();
  }
}
void Polyhedron::setupNeighbors() {}