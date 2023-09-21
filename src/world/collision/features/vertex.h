#pragma once
#include "feature.h"

template <typename T> class Vertex : public Feature<T> {
  vec3 localCoordinate;

  Vertex(T &parent, unsigned short ID, vec3 pos);
};