module world.camera;

import app.app;

Camera::Camera(const Transformable *parent, const float fov)
    : Transformable(parent),
      projection{
          glm::perspectiveFov(glm::radians(fov), static_cast<float>(app.WIDTH),
                              static_cast<float>(app.HEIGHT), 0.1f, 100.0f)} {
  setRotation(0, 0);
};
Camera::Camera(const float fov) : Camera(&Transformable::NO_PARENT, fov) {}

void Camera::update() {
  velocity = glm::normalize(velocity) * speed;
  translate(velocity);
}

const Mat4 &Camera::getProjection() const { return projection; }
const Mat4 Camera::getView() const {
  Vec3 eye{getPosition()};
  return glm::lookAt(eye, eye + forward, glm_util::Y_PLUS);
}
// const Vec3 &Camera::getPosition() const { return pos; }
float Camera::getSpeed() const { return speed; }
const Vec3 &Camera::getVelocity() const { return velocity; }
// const Vec3 &Camera::getForward() const { return forward; }
// const Vec3 &Camera::getUp() const { return up; }
// const Vec3 &Camera::getRight() const { return right; }
float Camera::getSensitivity() const { return sensitivity; }
float Camera::getYaw() const { return yaw; }
float Camera::getPitch() const { return pitch; }

// void Camera::move(const Vec3 &t) {
//   pos += t;
//   view = glm::translate(view, -t);
// }
// void Camera::setPosition(const Vec3 &t) { move(t - pos); }

void Camera::rotate(const float yaw, const float pitch) {
  setRotation(this->yaw + yaw, this->pitch + pitch);
}
void Camera::setRotation(const float yaw, const float pitch) {
  this->yaw = std::fmodf(yaw, 360);
  this->pitch = std::fmaxf(-89, std::fminf(pitch, 89));

  Rotatable::setRotation(glm_util::Y_PLUS, yaw);
  Rotatable::rotate(forward, pitch);
}

void Camera::resetVelocity() { velocity = {}; }
void Camera::addVelocity(const Vec3 &v) { velocity += v; }