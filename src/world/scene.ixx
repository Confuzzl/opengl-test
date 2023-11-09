export module world.scene;

import world.camera;
import world.game_object;
import util.memory;
import util.glm;
import <map>;
import <unordered_map>;

export struct Scene {
  Vec3 gravity{0.0f, -10.0f, 0.0f};

  using ObjectMap = std::map<unsigned int, UPtr<GameObject>>;
  using ObjectMap2 = std::unordered_map<unsigned int, UPtr<GameObject>>;
  ObjectMap objectMap;

  Camera camera{45};

  Scene();

  void start();
};