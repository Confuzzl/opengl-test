module world.camera;

import app.app;

Camera::Camera(const float fov)
    : projection{
          glm::perspectiveFov(glm::radians(fov), static_cast<float>(app.WIDTH),
                              static_cast<float>(app.HEIGHT), 0.1f, 100.0f)} {
  setRotate(0, 0);
}

void Camera::update() {
  glm::normalize(velocity);
  velocity *= speed;
  move(velocity);
}

const Mat4 &Camera::getProjection() const { return projection; }
const Mat4 &Camera::getView() const { return view; }
const Vec3 &Camera::getPosition() const { return pos; }
float Camera::getSpeed() const { return speed; }
const Vec3 &Camera::getVelocity() const { return velocity; }
const Vec3 &Camera::getForward() const { return forward; }
const Vec3 &Camera::getUp() const { return up; }
const Vec3 &Camera::getRight() const { return right; }
float Camera::getSensitivity() const { return sensitivity; }
float Camera::getYaw() const { return yaw; }
float Camera::getPitch() const { return pitch; }

void Camera::move(const Vec3 &t) {
  pos += t;
  view = glm::translate(view, -t);
}
void Camera::setPosition(const Vec3 &t) { move(t - pos); }

void Camera::rotate(const float yaw, const float pitch) {
  setRotate(this->yaw + yaw, this->pitch + pitch);
}
void Camera::setRotate(const float yaw, const float pitch) {
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

void Camera::resetVelocity() { velocity = {}; }
void Camera::addVelocity(const Vec3 &v) { velocity += v; }