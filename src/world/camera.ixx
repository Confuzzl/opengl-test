export module world.camera;

import util.glm;
import world.transform.transformable;
import <optional>;

export class Player;

export class Camera : public Transformable {
  std::optional<const Transformable *> parent;

  Mat4 projection;
  Mat4 view{1.0f};


  // Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};

  // Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};

  // Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};

  // Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
  Camera(std::optional<const Transformable *> parent, const float fov);
  // Vec3 forward{X_PLUS}, up{Y_PLUS}, right{Z_PLUS};
  float sensitivity = 30;
  float yaw = 0, pitch = 0;
  Camera(const Transformable *parent, const float fov);
  const Vec3 getGlobalPosition() const;

  Camera(const float fov);

  const Vec3 getGlobalPosition() const;

  //  const Vec3 &getUp() const;
  //  const Vec3 &getRight() const;
  //  const Vec3 &getUp() const;
  //  const Vec3 &getRight() const;
  //  const Vec3 &getUp() const;
  //  const Vec3 &getRight() const;
  float getSensitivity() const;
  float getYaw() const;
  float getPitch() const;

  void rotate(const float yaw, const float pitch);
  void setRotation(const float yaw, const float pitch);
};