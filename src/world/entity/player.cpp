module world.entity.player;

import world.camera;

Player::Player() : PhysicsObject(10) {}
Player::~Player() = default;

Camera &Player::getCamera() { return *camera; }