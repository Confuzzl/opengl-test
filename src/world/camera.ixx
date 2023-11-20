export module world.camera;

import util.glm;
import world.transform.transformable;
import <optional>;

export class Player;

export class Camera : public Transformable {
  std::optional<const Transformable *> parent;

  Mat4 projection;
  Mat4 view{1.0f};

  float sensitivity = 30;
  float yaw = 0, pitch = 0;

public:
  Camera(std::optional<const Transformable *> parent, const float fov);
  Camera(const float fov);

  const Mat4 &getProjection() const;
  const Mat4 getView() const;
  const Vec3 getGlobalPosition() const;

  float getSensitivity() const;
  float getYaw() const;
  float getPitch() const;

  void rotate(const float yaw, const float pitch);
  void setRotation(const float yaw, const float pitch);
};