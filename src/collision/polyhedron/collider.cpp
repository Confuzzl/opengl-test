module collision.collider;

import collision.feature.vertex;
import collision.feature.edge;
import collision.feature.face;
import util.debug;

unsigned int Collider::count = 0;

Collider::Collider(const unsigned short vertexCount,
                   const unsigned short faceCount, const Vec3List &coordinates,
                   const VEIndexList &vertexEdgeIndices,
                   const EVIndexList &edgeVertexIndices,
                   const EFIndexList &edgeFaceIndices,
                   const FEIndexList &faceEdgeIndices)
    : BasePolyhedron(coordinates), vertexEdgeIndices{vertexEdgeIndices},
      edgeVertexIndices{edgeVertexIndices}, edgeFaceIndices{edgeFaceIndices},
      faceEdgeIndices{faceEdgeIndices}, ID{count++} {
  if (vertexCount > 256)
    throw FeatureRelatedException{
        std::format("VERTEX COUNT ({}) EXCEEDS 256\n", vertexCount)};
  if (coordinates.size() != vertexCount)
    throw FeatureRelatedException{std::format(
        "COORDINATE SIZE DOES NOT EQUAL POLYHEDRON VERTEX COUNT ({} != {})\n",
        coordinates.size(), vertexCount)};
  if (vertexEdgeIndices.size() != vertexCount)
    throw FeatureRelatedException{std::format(
        "VERTEX-EDGE INDICES COUNT DOES NOT EQUAL VERTEX COUNT ({} != {})\n",
        vertexEdgeIndices.size(), vertexCount)};

  if (edgeVertexIndices.size() != edgeFaceIndices.size())
    throw FeatureRelatedException{
        std::format("EDGE-VERTEX INDICES COUNT DOES NOT EQUAL EDGE-FACE "
                    "INDICES COUNT ({} != {})\n",
                    edgeVertexIndices.size(), edgeFaceIndices.size())};
  if (edgeVertexIndices.size() > 256)
    throw FeatureRelatedException{
        std::format("EDGE COUNT OF EDGE-VERTEX INDICES ({}) EXCEEDS EDGE INDEX "
                    "RANGE (256)\n",
                    edgeVertexIndices.size())};
  if (edgeFaceIndices.size() > 256)
    throw FeatureRelatedException{std::format(
        "EDGE COUNT OF EDGE-FACE INDICES ({}) EXCEEDS EDGE INDEX RANGE (256)\n",
        edgeFaceIndices.size())};

  if (faceEdgeIndices.size() > 256)
    throw FeatureRelatedException{std::format(
        "FACE COUNT OF FACE-EDGE INDICES ({}) EXCEEDS FACE INDEX RANGE (256)\n",
        faceEdgeIndices.size())};
  if (faceEdgeIndices.size() != faceCount)
    throw FeatureRelatedException{
        std::format("FACE COUNT OF FACE-EDGE INDICES DOES NOT EQUAL FACE COUNT "
                    "({} != {})\n",
                    faceEdgeIndices.size(), faceCount)};

  vertices.reserve(coordinates.size());
  edges.reserve(edgeVertexIndices.size());
  faces.reserve(faceEdgeIndices.size());

  createFeatures();
  setupNeighbors();
}
Collider::~Collider() = default;

Vertex &Collider::addVertex(UPtr<Vertex> &&v) {
  // std::cout << std::format("ADDING vertex {} count: {}\n", (*v).ID,
  //                          v.use_count());
  return *vertices.emplace_back(std::move(v));
}
Edge &Collider::addEdge(UPtr<Edge> &&e) {
  // std::cout << std::format("ADDING edge {} count: {}\n", (*e).ID,
  //                          e.use_count());
  return *edges.emplace_back(std::move(e));
}
Face &Collider::addFace(UPtr<Face> &&f) {
  // std::cout << std::format("ADDING face {} count: {}\n", (*f).ID,
  //                          f.use_count());
  return *faces.emplace_back(std::move(f));
}

void Collider::createFeatures() {
  for (unsigned char i = 0; const auto &v : coordinates) {
    addVertex(std::make_unique<Vertex>(*this, i++, v));
  }
  for (unsigned char i = 0; const auto &pair : edgeVertexIndices) {
    unsigned char tailIndex = pair[0], headIndex = pair[1];
    addEdge(std::make_unique<Edge>(*this, i++, *vertices[tailIndex],
                                   *vertices[headIndex]));
  }
  for (unsigned char i = 0; const auto &face : faceEdgeIndices) {
    Face &f = addFace(std::make_unique<Face>(
        *this, i++, static_cast<unsigned short>(face.size())));
    for (const unsigned char &index : face)
      f.addEdge(*edges[index]);
  }
}
void Collider::setupNeighbors() {
  for (unsigned char i = 0; const auto &indices : vertexEdgeIndices) {
    for (const unsigned char index : indices)
      vertices[i]->addNeighbor(*edges[index]);
    vertices[i]->finishCreation();
    i++;
  }
  for (unsigned char i = 0; const auto &pair : edgeFaceIndices) {
    edges[i]->setNeighbors(faces[pair[0]].get(), faces[pair[1]].get());
    edges[i]->finishCreation();
    i++;
  }
  for (auto &face : faces) {
    face->finishCreation();
  }
}