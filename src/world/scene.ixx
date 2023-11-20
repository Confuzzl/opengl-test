export module world.scene;

import util.memory;
import util.glm;
import <map>;
import <unordered_map>;

export class GameObject;
export class Player;

export struct Scene {
  Vec3 gravity{0.0f, -10.0f, 0.0f};

  using ObjectMap = std::map<unsigned int, UPtr<GameObject>>;
  using ObjectMap2 = std::unordered_map<unsigned int, UPtr<GameObject>>;
  ObjectMap objectMap{};

  GameObject *testObject;

  UPtr<Player> player{std::make_unique<Player>()};

  Scene();
  ~Scene();

  void start();
};