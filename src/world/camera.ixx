export module world.camera;

import util.glm;

export class Camera {
  Mat4 projection;
  Mat4 view{1.0f};

  Vec3 pos{};
  float speed = 2;
  Vec3 velocity{};

  Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
  float sensitivity = 30;
  float yaw = 0, pitch = 0;

public:
  Camera(const float fov);

  void update();

  const Mat4 &getProjection();
  const Mat4 &getView();
  const Vec3 &getPosition();
  const float getSpeed();
  const Vec3 &getVelocity();
  const Vec3 &getForward();
  const Vec3 &getUp();
  const Vec3 &getRight();
  const float getSensitivity();

  void move(const Vec3 &t);
  void setPosition(const Vec3 &t);

  void rotate(const float yaw, const float pitch);
  void setRotate(const float yaw, const float pitch);

  void resetVelocity();
  void addVelocity(const Vec3 &v);
};