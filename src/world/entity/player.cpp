module world.entity.player;

import world.camera;

Player::Player()
    : PhysicsObject(10), camera{std::make_unique<Camera>(this, 45.0f)},
      speed{4} {}
Player::~Player() = default;

Camera &Player::getCamera() { return *camera; }