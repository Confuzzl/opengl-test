module world.camera;

import app.app;
import util.debug;

Camera::Camera(std::optional<const Transformable *> parent, const float fov)
    : parent{parent}, projection{glm::perspectiveFov(
                          glm::radians(fov), static_cast<float>(mainApp.WIDTH),
                          static_cast<float>(mainApp.HEIGHT), 0.1f, 100.0f)} {
  setRotation(0, 0);
};
Camera::Camera(const float fov) : Camera(std::nullopt, fov) {}

const Mat4 &Camera::getProjection() const { return projection; }
const Mat4 Camera::getView() const {
  Vec3 eye{getGlobalPosition()};
  return glm::lookAt(eye, eye + forward, glm_util::Y);
  // return glm::translate(glm::lookAt(glm_util::ZERO, forward, glm_util::Y),
  //                       -getGlobalPosition());
}
const Vec3 Camera::getGlobalPosition() const {
  Vec3 out{getPosition()};
  if (parent)
    out += parent.value()->getPosition();
  return out;
}

float Camera::getSensitivity() const { return sensitivity; }
float Camera::getYaw() const { return yaw; }
float Camera::getPitch() const { return pitch; }

void Camera::rotate(const float yaw, const float pitch) {
  setRotation(this->yaw + yaw, this->pitch + pitch);
}
void Camera::setRotation(const float yaw, const float pitch) {
  this->yaw = std::fmodf(yaw, 360);
  this->pitch = std::fmaxf(-89.5, std::fminf(pitch, 89.5));

  Rotatable::setRotation(glm_util::Y, this->yaw);
  Rotatable::rotate(right, this->pitch);
}