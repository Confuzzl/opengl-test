export module world.scene;

// import world.camera;
// import world.game_object;
// import world.entity.player;
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

  // UPtr<Camera> camera{std::make_unique<Camera>(45.0f)};
  UPtr<Player> player{std::make_unique<Player>()};

  Scene();
  ~Scene();

  void start();
};