#pragma once
#include "collision/transformable.h"
#include <vector>

class BasePolyhedron : public Transformable {
public:
  typedef std::vector<vec3> Vec3List;

protected:
  const Vec3List coordinates;
  std::vector<glm::u8vec2> edgeVertexIndices;
  BasePolyhedron(const Vec3List &coordinates);
};