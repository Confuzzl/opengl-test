#include "vertex.h"

template <typename T>
Vertex<T>::Vertex(T &parent, unsigned short ID, vec3 pos)
    : Feature<T>(parent, ID), localCoordinate{pos} {}