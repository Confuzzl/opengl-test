#include "polyhedron.h"
#include "features/edge.h"
#include "features/face.h"
#include "features/vertex.h"

Polyhedron::Polyhedron(const std::vector<vec3> &coordinates)
    : coordinates{coordinates} {}
Polyhedron::~Polyhedron() = default;

void Polyhedron::createFeatures() {}
void Polyhedron::setupNeighbors() {}