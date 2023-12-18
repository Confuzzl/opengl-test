module;

#include "util/gl_utils.hpp"

module app.input.input_handler;

import world.game_object;
import app.update_cycle;
import util.gl_types;
import util.debug;

const InputHandler::Key::Callback InputHandler::Key::NONE{[](const double) {}};

void InputHandler::processInput(const double dt) {
  for (auto &[keycode, key] : keys)
    key(dt);
}

std::map<int, InputHandler::Key> InputHandler::keys{
    {GLFW_KEY_ESCAPE,
     {[](const double) { glfwSetWindowShouldClose(mainApp.window, GL_TRUE); }}},
    {GLFW_KEY_1, {[](const double) {
       mainApp.renderingHandler.primitive = GLPrimitive::TRIANGLES;
     }}},
    {GLFW_KEY_2, {[](const double) {
       mainApp.renderingHandler.primitive = GLPrimitive::LINE_LOOP;
     }}},
    {GLFW_KEY_3, {[](const double) {
       mainApp.renderingHandler.primitive = GLPrimitive::POINTS;
     }}},
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
    {GLFW_KEY_Q,
     {[](const double) {
        mainScene.testObject->translate({1, 0, 0});
      },
      InputHandler::Key::NONE,
      [](const double) {
        mainScene.testObject->translate({-1, 0, 0});
      },
      InputHandler::Key::NONE}},
};

void InputHandler::keyCallback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  if (not keys.contains(key))
    return;
  // prev = curr;
  // curr = glfwGetTime();
  // std::cout << std::format("{}: {} ({:.5f}, {:.5f})\n",
  //                          glfwGetKeyName(key, scancode),
  //                          modes[action], curr, curr - prev);
  // keys.at(key).on = action;
  keys.at(key).change(action);
}

void InputHandler::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
  if (not mainApp.cursorSnap) {
    mainApp.prevX = xpos;
    mainApp.prevY = ypos;
    mainApp.cursorSnap = true;
  }
  const float dx = static_cast<float>(mainApp.prevX - xpos);
  const float dy = static_cast<float>(mainApp.prevY - ypos);
  mainApp.prevX = xpos;
  mainApp.prevY = ypos;

  const float magnitude =
      static_cast<float>(mainApp.updateCycle->dt * mainCamera.getSensitivity());
  mainCamera.rotate(dx * magnitude, dy * magnitude);
}

void InputHandler::scrollCallback(GLFWwindow *window, double xpos,
                                  double ypos) {
  mainPlayer.speed =
      std::fmax(0.0f, static_cast<float>(mainPlayer.speed + ypos * 0.25));
}
