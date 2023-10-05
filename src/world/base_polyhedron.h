#pragma once
#include "collision/transformable.h"
#include "util/vector_utils.h"

class BasePolyhedron : public Transformable {
public:
  using Vec3List = Vector<Vec3>;

protected:
  const Vec3List coordinates;

  BasePolyhedron(const Vec3List &coordinates);
};