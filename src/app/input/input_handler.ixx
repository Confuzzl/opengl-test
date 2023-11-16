module;

#include "util/gl_utils.hpp"

export module app.input.input_handler;

import app.input.key;
import util.glm;
import <map>;
import <functional>;

import app.app;
import world.scene;
import world.camera;
import app.update_cycle;

export struct InputHandler {
private:
  Camera &camera;

  std::map<int, Key> keys{
      {GLFW_KEY_ESCAPE,
       {[](int, int, int) { glfwSetWindowShouldClose(app.window, GL_TRUE); }}},
      {GLFW_KEY_1, {[](int, int, int) { app.mainPrimitive = GL_TRIANGLES; }}},
      {GLFW_KEY_2, {[](int, int, int) { app.mainPrimitive = GL_LINE_LOOP; }}},
      {GLFW_KEY_3, {[](int, int, int) { app.mainPrimitive = GL_POINTS; }}},
      {GLFW_KEY_W, {[](int, int, int) {
         // Camera &cam{*app.scene->camera};
         //  cam.addVelocity(
         //      cam.getForward() *
         //      static_cast<float>(app.updateCycle->delta * cam.getSpeed()));
       }}}};

public:
  InputHandler();

  void callback(GLFWwindow *window, int key, int scancode, int action,
                int mods);
};