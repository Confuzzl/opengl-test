#pragma once
#include "collision/transformable.h"
#include "util/polyhedron_utils.h"

class BasePolyhedron : public Transformable {
protected:
  const Vec3List coordinates;

  BasePolyhedron(const Vec3List &coordinates);
};