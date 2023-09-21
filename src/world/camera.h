#pragma once
#include "util/glm_utils.h"
class Camera {
public:
  mat4 projection;
  mat4 view{1.0f};

  vec3 pos{};
  float speed = 2;
  vec3 velocity{};

  vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
  float sensitivity = 30;
  float yaw = 0, pitch = 0;

  Camera(float fov);

  void update();

  void move(vec3 t);
  void setPosition(vec3 t);

  void rotate(float yaw, float pitch);
  void setRotate(float yaw, float pitch);
};