#include "polyhedron.h"
#include "features/edge.h"
#include "features/face.h"
#include "features/vertex.h"

template <typename T>
Polyhedron<T>::Polyhedron(const std::vector<vec3> &coordinates)
    : coordinates{coordinates} {}
template <typename T> Polyhedron<T>::~Polyhedron() = default;

template <typename T> void Polyhedron<T>::createFeatures() {}
template <typename T> void Polyhedron<T>::setupNeighbors() {}