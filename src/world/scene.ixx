export module world.scene;

import util.memory;
import util.glm;
import <typeindex>;
import <map>;
import <unordered_map>;

// export class GameObject;
export class Player;

export struct Scene {
  Vec3 gravity{0.0f, -10.0f, 0.0f};

  UPtr<Player> player{std::make_unique<Player>()};

  Scene();
  ~Scene();

  void start();
};