#include "polyhedron.h"
#include "features/edge.h"
#include "features/face.h"
#include "features/vertex.h"
#include "util/debug_utils.h"

unsigned int Polyhedron::count = 0;

Polyhedron::Polyhedron(const unsigned short vertexCount,
                       const Vec3List &coordinates,
                       const VertexNeighborList &vertexEdgeIndices,
                       const EdgeNeighborList &edgeVertexIndices,
                       const EdgeNeighborList &edgeFaceIndices,
                       const FaceNeighborList &faceEdgeIndices)
    : BasePolyhedron(coordinates), vertexEdgeIndices{vertexEdgeIndices},
      edgeVertexIndices{edgeVertexIndices}, edgeFaceIndices{edgeFaceIndices},
      faceEdgeIndices{faceEdgeIndices}, ID{count++} {
  if (vertexCount > 256)
    throw VerticesSizeException("VERTEX COUNT EXCEEDS 256");
  if (coordinates.size() != vertexCount)
    throw VerticesSizeException{std::format(
        "COORDINATE SIZE DOES NOT EQUAL POLYHEDRON VERTEX COUNT ({})",
        vertexCount)};
  if (vertexEdgeIndices.size() != vertexCount)
    throw FeatureRelatedException{std::format(
        "VERTEX-EDGE INDICES COUNT DOES NOT EQUAL VERTEX COUNT ({})",
        vertexCount)};

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

  createFeatures();
  setupNeighbors();
}
// Polyhedron::~Polyhedron() = default;

SPtr<Vertex> &Polyhedron::addVertex(SPtr<Vertex> &&v) {
  // std::cout << std::format("ADDING vertex {} count: {}\n", (*v).ID,
  //                          v.use_count());
  return vertices.emplace_back(v);
}
SPtr<Edge> &Polyhedron::addEdge(SPtr<Edge> &&e) {
  // std::cout << std::format("ADDING edge {} count: {}\n", (*e).ID,
  //                          e.use_count());
  return edges.emplace_back(e);
}
SPtr<Face> &Polyhedron::addFace(SPtr<Face> &&f) {
  // std::cout << std::format("ADDING face {} count: {}\n", (*f).ID,
  //                          f.use_count());
  return faces.emplace_back(f);
}

void Polyhedron::createFeatures() {
  for (unsigned char i = 0; const Vec3 &v : coordinates) {
    addVertex(std::make_shared<Vertex>(*this, i++, v));
  }
  for (unsigned char i = 0; const auto &pair : edgeVertexIndices) {
    unsigned char tailIndex = pair[0], headIndex = pair[1];
    addEdge(std::make_shared<Edge>(*this, i++, vertices[tailIndex],
                                   vertices[headIndex]));
  }
  for (unsigned char i = 0; const auto &face : faceEdgeIndices) {
    SPtr<Face> &f = addFace(
        std::make_shared<Face>(*this, i++, (unsigned short)face.size()));
    for (const unsigned char &index : face)
      (*f).addEdge(edges[index]);
  }
}
void Polyhedron::setupNeighbors() {
  for (unsigned char i = 0; const auto &indices : vertexEdgeIndices) {
    for (const unsigned char index : indices)
      (*vertices[i]).addNeighbor(edges[index]);
    i++;
  }

  for (unsigned char i = 0; const auto &pair : edgeFaceIndices)
    (*edges[i++]).setNeighbors(faces[pair[0]], faces[pair[1]]);

  for (const auto &face : faces)
    (*face).finishCreation();
}