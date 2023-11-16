export module world.camera;

import util.glm;
import world.transform.transformable;

export class Player;

export class Camera {
  Mat4 projection;
  Mat4 view{1.0f};

  Vec3 pos{};
  float speed{2};
  Vec3 velocity{};

  Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
  float sensitivity = 30;
  float yaw = 0, pitch = 0;

public:
  Camera(const float fov);

  void update();

  const Mat4 &getProjection() const;
  const Mat4 &getView() const;
  const Vec3 &getPosition() const;
  float getSpeed() const;
  const Vec3 &getVelocity() const;
  const Vec3 &getForward() const;
  const Vec3 &getUp() const;
  const Vec3 &getRight() const;
  float getSensitivity() const;
  float getYaw() const;
  float getPitch() const;

  void move(const Vec3 &t);
  void setPosition(const Vec3 &t);

  void rotate(const float yaw, const float pitch);
  void setRotate(const float yaw, const float pitch);

  void resetVelocity();
  void addVelocity(const Vec3 &v);
};