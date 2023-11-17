export module world.camera;

import util.glm;
import world.transform.transformable;

export class Player;

export class Camera : public Transformable {
  Mat4 projection;
  Mat4 view{1.0f};

  float speed{2};
  Vec3 velocity{};

  float sensitivity = 30;
  float yaw = 0, pitch = 0;

public:
  Camera(const Transformable *parent, const float fov);
  Camera(const float fov);

  void update();

  const Mat4 &getProjection() const;
  const Mat4 getView() const;

  float getSpeed() const;
  const Vec3 &getVelocity() const;

  float getSensitivity() const;
  float getYaw() const;
  float getPitch() const;

  void rotate(const float yaw, const float pitch);
  void setRotation(const float yaw, const float pitch);

  void resetVelocity();
  void addVelocity(const Vec3 &v);
};