#pragma once
#include "util/glm_utils.h"
#include "util/vector_utils.h"

struct UVListFactory {
  using UVList = Vector2D<glm::lowp_u16vec2>;

  UVList faceUVs;

private:
  UVListFactory(const UVList &faceUVs);

public:
  static UVList generateFromPixels(const UVList &facePixels);
  static UVList generateFromUVs(const Vector2D<Vec2> &faceUVs);
};