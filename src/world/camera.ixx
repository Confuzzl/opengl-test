export module world.camera;

import util.glm;

export class Camera {
public:
  Mat4 projection;
  Mat4 view{1.0f};

  Vec3 pos{};
  float speed = 2;
  Vec3 velocity{};

  Vec3 forward{X_PLUS_MODULE}, up{Y_PLUS_MODULE}, right{Z_PLUS_MODULE};
  float sensitivity = 30;
  float yaw = 0, pitch = 0;

  Camera(float fov);

  void update();

  void move(Vec3 t);
  void setPosition(Vec3 t);

  void rotate(float yaw, float pitch);
  void setRotate(float yaw, float pitch);
};