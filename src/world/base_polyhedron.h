#pragma once
#include "collision/transformable.h"
#include "util/vector_utils.h"
#include <memory>

class BasePolyhedron : public Transformable {
public:
  using Vec3List = Vector<vec3>;
  /*template <typename T> using UPtrList = Vector<std::unique_ptr<T>>;
  template <typename T> using SPtrList = Vector<std::shared_ptr<T>>;*/

protected:
  const Vec3List coordinates;
  Vector<glm::u8vec2> edgeVertexIndices;
  BasePolyhedron(const Vec3List &coordinates);
};