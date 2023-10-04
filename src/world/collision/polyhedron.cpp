#include "polyhedron.h"
#include "features/edge.h"
#include "features/face.h"
#include "features/vertex.h"

Polyhedron::Polyhedron(const Vec3List &coordinates)
    : BasePolyhedron(coordinates) {}
Polyhedron::~Polyhedron() = default;

void Polyhedron::verifyVertices() {}
void Polyhedron::verifyEdges() {}
void Polyhedron::verifyFaces() {}

void Polyhedron::createFeatures() {}
void Polyhedron::setupNeighbors() {}