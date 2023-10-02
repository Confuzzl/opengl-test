#include "polyhedron.h"
#include "features/vertex.h"
#include "features/edge.h"
#include "features/face.h"

Polyhedron::Polyhedron(const std::vector<vec3> &coordinates)
    : coordinates{coordinates} {}
Polyhedron::~Polyhedron() = default;