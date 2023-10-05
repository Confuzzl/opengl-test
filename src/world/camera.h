#pragma once
#include "util/glm_utils.h"
class Camera {
public:
  Mat4 projection;
  Mat4 view{1.0f};

  Vec3 pos{};
  float speed = 2;
  Vec3 velocity{};

  Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
  float sensitivity = 30;
  float yaw = 0, pitch = 0;

  Camera(float fov);

  void update();

  void move(Vec3 t);
  void setPosition(Vec3 t);

  void rotate(float yaw, float pitch);
  void setRotate(float yaw, float pitch);
};