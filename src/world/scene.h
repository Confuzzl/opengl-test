#pragma once
#include "camera.h"
#include "collision/prism.h"
#include "util/glm_utils.h"
#include <unordered_set>
struct Scene {
  Vec3 gravity{0.0f, -10.0f, 0.0f};
  std::unordered_set<Prism *> objects{};
  Camera camera{45};

  Scene();
};
