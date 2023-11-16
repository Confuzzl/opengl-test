module;

#include "util/gl_utils.hpp"

module app.input.input_handler;

// import app.app;
// import world.scene;
// import world.camera;
// import app.update_cycle;

// std::map<int, std::pair<std::function<Vec3(const Camera *)>, float>>
//     InputHandler::movementMaps{{GLFW_KEY_W, {&Camera::getForward, +1.0f}}};
// std::map<int, Key> InputHandler::keys{
//    {GLFW_KEY_ESCAPE,
//     {[](int, int, int) { glfwSetWindowShouldClose(app.window, GL_TRUE); }}},
//    {GLFW_KEY_1, {[](int, int, int) { app.mainPrimitive = GL_TRIANGLES; }}},
//    {GLFW_KEY_2, {[](int, int, int) { app.mainPrimitive = GL_LINE_LOOP; }}},
//    {GLFW_KEY_3, {[](int, int, int) { app.mainPrimitive = GL_POINTS; }}},
//    {GLFW_KEY_W, {[](int, int, int) {
//       // Camera &cam{*app.scene->camera};
//       //  cam.addVelocity(
//       //      cam.getForward() *
//       //      static_cast<float>(app.updateCycle->delta * cam.getSpeed()));
//     }}}};

void InputHandler::callback(GLFWwindow *window, int key, int scancode,
                            int action, int mods) {
  Key &k{keys.at(key)};
  k.callback(scancode, action, mods);
  k.on = action == GLFW_PRESS;
}