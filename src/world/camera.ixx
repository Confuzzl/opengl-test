export module world.camera;

import util.glm;

export class Camera {
public:
  Mat4 projection;
  Mat4 view{1.0f};

  Vec3 pos{};
  float speed = 2;
  Vec3 velocity{};

  Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
  float sensitivity = 30;
  float yaw = 0, pitch = 0;

  Camera(const float fov);

  void update();

  void move(const Vec3 t);
  void setPosition(const Vec3 t);

  void rotate(const float yaw, const float pitch);
  void setRotate(const float yaw, const float pitch);
};