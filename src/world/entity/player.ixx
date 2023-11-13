export module world.entity.player;

import util.memory;

export class Camera;

export class Player {
  UPtr<Camera> camera;

public:
  Player();
  ~Player();

  Camera &getCamera();
};