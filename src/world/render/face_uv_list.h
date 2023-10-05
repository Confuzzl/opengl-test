#pragma once
#include "util/glm_utils.h"
#include "util/vector_utils.h"

struct FaceUVList {
  using UVList = Vector2D<glm::lowp_u16vec2>;

  UVList faceUVs;

public:
  static FaceUVList generateFromPixels(const UVList &facePixels);
  static FaceUVList generateFromUVs(const Vector2D<Vec2> &faceUVs);
};