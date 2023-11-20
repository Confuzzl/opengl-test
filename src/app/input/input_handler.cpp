module;

#include "util/gl_utils.hpp"

module app.input.input_handler;

import world.game_object;
import util.debug;

const InputHandler::Key::ProcessFunction InputHandler::Key::NO_PROCESS{
    [](const double) {}};

std::map<int, InputHandler::Key> InputHandler::keys{
    {GLFW_KEY_ESCAPE,
     {[](const double) { glfwSetWindowShouldClose(mainApp.window, GL_TRUE); }}},
    {GLFW_KEY_1, {[](const double) { mainApp.mainPrimitive = GL_TRIANGLES; }}},
    {GLFW_KEY_2, {[](const double) { mainApp.mainPrimitive = GL_LINE_LOOP; }}},
    {GLFW_KEY_3, {[](const double) { mainApp.mainPrimitive = GL_POINTS; }}},
    {GLFW_KEY_W,
     {InputHandler::Key::playerMoveFunction(
         [] { return mainCamera.getForwardFlat(); }, +1)}},
    {GLFW_KEY_A,
     {InputHandler::Key::playerMoveFunction(
         [] { return mainCamera.getRight(); }, -1)}},
    {GLFW_KEY_S,
     {InputHandler::Key::playerMoveFunction(
         [] { return mainCamera.getForwardFlat(); }, -1)}},
    {GLFW_KEY_D,
     {InputHandler::Key::playerMoveFunction(
         [] { return mainCamera.getRight(); }, +1)}},
    {GLFW_KEY_SPACE,
     {InputHandler::Key::playerMoveFunction([] { return glm_util::Y; }, +1)}},
    {GLFW_KEY_LEFT_CONTROL,
     {InputHandler::Key::playerMoveFunction([] { return glm_util::Y; }, -1)}},
    {GLFW_KEY_UP, {InputHandler::Key::cameraRotateFunction(0, +1)}},
    {GLFW_KEY_LEFT, {InputHandler::Key::cameraRotateFunction(+1, 0)}},
    {GLFW_KEY_DOWN, {InputHandler::Key::cameraRotateFunction(0, -1)}},
    {GLFW_KEY_RIGHT, {InputHandler::Key::cameraRotateFunction(-1, 0)}},
};

// static const std::string modes[3]{"RELEASE", "PRESS",
// "REPEAT"}; static double prev = 0, curr = 0;

void InputHandler::callback(GLFWwindow *window, int key, int scancode,
                            int action, int mods) {
  if (not keys.contains(key))
    return;
  // prev = curr;
  // curr = glfwGetTime();
  // std::cout << std::format("{}: {} ({:.5f}, {:.5f})\n",
  //                          glfwGetKeyName(key, scancode),
  //                          modes[action], curr, curr - prev);
  keys.at(key).on = action;
}