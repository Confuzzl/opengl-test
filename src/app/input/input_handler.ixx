export module app.input.input_handler;

import app.input.key;
import util.glm;
import <map>;
import <functional>;

export struct GLFWwindow;
export class Camera;

export struct InputHandler {
private:
  // static std::map<int, std::function<float()>> magnitudes;
  static std::map<int, std::pair<std::function<Vec3(const Camera *)>, float>>
      movementMaps;
  static std::map<int, Key> keys;

public:
  static void callback(GLFWwindow *window, int key, int scancode, int action,
                       int mods);
};