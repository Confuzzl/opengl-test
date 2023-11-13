module world.entity.player;

import world.camera;

Player::Player() {}
Player::~Player() = default;

Camera &Player::getCamera() { return *camera; }