export module world.scene;

import world.camera;
import world.collision.prism;
import world.game_object;
import util.memory;
import util.glm;
import <unordered_set>;

export struct Scene {
  Vec3 gravity{0.0f, -10.0f, 0.0f};
  std::unordered_set<Prism *> objects{};
  std::unordered_set<GameObject *> gameObjects{};
  Camera camera{45};

  Scene();
};