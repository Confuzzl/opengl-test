export module app.input.input_handler;

import app.input.key;
import util.glm;
import <map>;
import <functional>;

export struct GLFWwindow;
export class Camera;

export struct InputHandler {
private:
  Camera &camera;

  std::map<int, Key> keys;

public:
  InputHandler();

  void callback(GLFWwindow *window, int key, int scancode, int action,
                int mods);
};