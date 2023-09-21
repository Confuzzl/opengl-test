#pragma once
#include "world/collision/polyhedron.h"

// template <template <std::size_t, std::size_t, std::size_t> typename
// Polyhedron,
//           std::size_t v, std::size_t e, std::size_t f>
template <IsPolyhedron T> class Feature {
  // static_assert(std::same_as < T, Polyhedron<v, e, f>);
  T &parent;
  unsigned short ID;

  Feature(T &parent, unsigned short ID);
};
