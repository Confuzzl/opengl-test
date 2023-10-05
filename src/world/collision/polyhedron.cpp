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
        "VERTEX COUNT OF COORDINATES EXCEEDS EDGE-VERTEX INDEX RANGE (256)"};
  if (edgeVertexIndices.size() != edgeFaceIndices.size())
    throw FeatureRelatedException{
        "EDGE-VERTEX INDICES COUNT DOES NOT EQUAL EDGE-FACE INDICES COUNT"};
  if (edgeVertexIndices.size() > 256)
    throw FeatureRelatedException{"EDGE COUNT OF EDGE-VERTEX INDICES EXCEEDS "
                                  "FACE-EDGE INDEX RANGE (256)"};
  if (edgeFaceIndices.size() > 256)
    throw FeatureRelatedException{
        "EDGE COUNT OF EDGE-FACE INDICES EXCEEDS FACE-EDGE INDEX RANGE (256)"};
  if (faceEdgeIndices.size() > 256)
    throw FeatureRelatedException{
        "FACE COUNT OF FACE-EDGE INDICES EXCEEDS EDGE-FACE INDEX RANGE (256)"};

  vertices.reserve(coordinates.size());
  edges.reserve(edgeVertexIndices.size());
  faces.reserve(faceEdgeIndices.size());
}
Polyhedron::~Polyhedron() = default;

void Polyhedron::createFeatures() {
  for (unsigned short i = 0; const Vec3 &v : coordinates) {
    vertices.emplace_back(*this, i++, v);
  }
  for (unsigned short i = 0; const auto &pair : edgeVertexIndices) {
    unsigned char tailIndex = pair[0];
    unsigned char headIndex = pair[1];
    edges.emplace_back(*this, i++, vertices[tailIndex], vertices[headIndex]);
  }
  for (unsigned short i = 0; const auto &face : faceEdgeIndices) {
    for (const unsigned char &index : face) {
    
    }
  }
}
void Polyhedron::setupNeighbors() {}