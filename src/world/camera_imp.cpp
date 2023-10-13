module;

module world.camera;

import app.app;

Camera::Camera(float fov)
    : projection{glm::perspectiveFov(glm::radians(fov), (float)appModule.WIDTH,
                                     (float)appModule.HEIGHT, 0.1f, 100.0f)} {
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

  forward = rotateAroundAxis(X_PLUS_MODULE, Y_PLUS_MODULE, yaw);
  up = rotateAroundAxis(Y_PLUS_MODULE, Y_PLUS_MODULE, yaw);
  right = rotateAroundAxis(Z_PLUS_MODULE, Y_PLUS_MODULE, yaw);

  forward = rotateAroundAxis(forward, right, pitch);
  up = rotateAroundAxis(up, right, pitch);
  right = rotateAroundAxis(right, right, pitch);

  view = glm::lookAt(pos, pos + forward, Y_PLUS_MODULE);
}