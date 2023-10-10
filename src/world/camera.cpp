#include "world/camera.h"
#include "app/app.h"
#include "util/debug_utils.h"

Camera::Camera(float fov)
    : projection{glm::perspectiveFov(glm::radians(fov), (float)app.WIDTH,
                                     (float)app.HEIGHT, 0.1f, 100.0f)} {
  setRotate(0, 0);
}

void Camera::update() {
  glm::normalize(velocity);
  velocity *= speed;
  move(velocity);
}

void Camera::move(Vec3 t) {
  pos += t;
  view = glm::translate(view, -t);
}
void Camera::setPosition(Vec3 t) { move(t - pos); }

void Camera::rotate(float yaw, float pitch) {
  setRotate(this->yaw + yaw, this->pitch + pitch);
}
void Camera::setRotate(float yaw, float pitch) {
  this->yaw = std::fmodf(yaw, 360);
  this->pitch = std::fmaxf(-89, std::fminf(pitch, 89));

  forward = rotateAroundAxis(X_PLUS, Y_PLUS, yaw);
  up = rotateAroundAxis(Y_PLUS, Y_PLUS, yaw);
  right = rotateAroundAxis(Z_PLUS, Y_PLUS, yaw);

  forward = rotateAroundAxis(forward, right, pitch);
  up = rotateAroundAxis(up, right, pitch);
  right = rotateAroundAxis(right, right, pitch);

  view = glm::lookAt(pos, pos + forward, Y_PLUS);
}