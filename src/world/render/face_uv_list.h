#pragma once
#include "util/glm_utils.h"
#include <vector>

struct FaceUVList {
  std::vector<std::vector<glm::lowp_u16vec2>> faceUVs;

  // private:
  //   FaceTextureList(std::vector<std::vector<glm::lowp_u16vec2>> faceUVs);
  //   FaceTextureList(const FaceTextureList &f) = default;
  //   FaceTextureList(FaceTextureList &&f) = default;

public:
  static FaceUVList generateFromPixels(
      const std::vector<std::vector<glm::lowp_u16vec2>> &facePixels);
  static FaceUVList
  generateFromUVs(const std::vector<std::vector<vec2>> &faceUVs);
};