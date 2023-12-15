module;

#include "util/gl_utils.hpp"
#include <algorithm>
#include <numeric>

module app.app;

import app.update_cycle;
// import wrapper.program.programs;
import wrapper.tex_object;
import app.text.font;
import world.game_object;
// import rendering.renderable;
import app.text.text_corners;
import rendering.shaders.global;
import util.vector;
import util.debug;

import app.input.input_handler;

const Mat4 App::UI_MAT{glm::ortho(0.0f, static_cast<float>(App::WIDTH), 0.0f,
                                  static_cast<float>(App::HEIGHT))};

App::App()
    : loopCycle{std::make_unique<UpdateCycle>(0)},
      updateCycle{std::make_unique<UpdateCycle>(120)},
      frameCycle{std::make_unique<UpdateCycle>(60)} {
  std::cout << "app constructing\n";
  glfwInit();
  frameCycle->bottleNeck(
      glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate);

  createWindow();

  // Shaders::_3D::COLTEX.create();
  // Shaders::_2D::FONT.create();

  Shaders::createAll();

  try {
    atlas->initTexture();
    consolas->initAtlas();
  } catch (const std::runtime_error &e) {
    catchException(e);
  }

  std::cout << "app finished constructing\n";
}
App::~App() {
  glfwDestroyWindow(window);
  glfwTerminate();
  std::cout << std::format("app terminated at {:.2f}s\n", glfwGetTime());
}

void App::start() {
  scene->start();

  glPointSize(10);
  glLineWidth(5);
  glPolygonMode(GL_FRONT, GL_FILL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glfwSwapInterval(0);

  while (!glfwWindowShouldClose(window)) {
    try {
      double currentTime = glfwGetTime();

      loopCycle->pushNewTime(currentTime);
      if (updateCycle->pastLength(currentTime)) {
        startUpdate(currentTime);
      }
      if (frameCycle->pastLength(currentTime)) {
        startFrame(currentTime);
      }
      if (currentTime - seconds >= 1) {
        seconds++;
        loopCycle->pushCount();
        updateCycle->pushCount();
        frameCycle->pushCount();
      }
    } catch (const std::runtime_error &e) {
      catchException(e);
    }
  }
}
void App::startUpdate(const double t) {
  updateCycle->pushNewTime(t);
  glfwPollEvents();
  processInput(updateCycle->dt);
  mainScene.testObject->update(updateCycle->dt);
}
void App::startFrame(const double t) {
  frameCycle->pushNewTime(t);

  glClearColor(0, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawScene();

  Text::resetAllTextOffsets();

  const Camera &cam{scene->player->getCamera()};
  const Vec3 pos{cam.getPosition()};
  Text::TOP_LT.drawText(
      std::format("POS: {:+.3f} {:+.3f} {:+.3f}", pos[0], pos[1], pos[2]));
  Text::TOP_LT.drawText(
      std::format("CAM: {:+.3f} {:+.3f}", cam.getYaw(), cam.getPitch()));

  Text::TOP_RT.drawText(std::format("FPS: {}", frameCycle->prevCount));
  Text::TOP_RT.drawText(std::format("Time: {:.2f}s", t));
  Text::TOP_RT.drawText(std::format("LPS: {}", loopCycle->prevCount));
  Text::TOP_RT.drawText(std::format("UPS: {}", updateCycle->prevCount));

  Text::BOT_RT.drawText(std::format("{:.2f}", mainPlayer.speed));

  glfwSwapBuffers(window);
}

void App::createWindow() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_SAMPLES, 4);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Test", NULL, NULL);

  if (window == NULL) {
    glfwTerminate();
    throw FailedWindowCreationException{"WINDOW FAILED TO BE CREATED"};
  }
  glfwMakeContextCurrent(window);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, InputHandler::mouseCallback);
  glfwSetScrollCallback(window, InputHandler::scrollCallback);
  glfwSetKeyCallback(window, InputHandler::keyCallback);

  gladLoadGL();
  glViewport(0, 0, WIDTH, HEIGHT);
}

void App::catchException(const std::runtime_error &e) {
  std::cout << e.what();
  glfwSetWindowShouldClose(mainApp.window, GL_TRUE);
}

void App::processInput(const double dt) {
  for (auto &[keycode, key] : InputHandler::keys) {
    key(dt);
  }
}

void App::drawScene() {
  Shaders::_3D::COLTEX.useProgram();
  Shaders::_3D::COLTEX.setMat4("projection", mainCamera.getProjection());

  for (const auto &[ID, obj] : mainScene.objectMap) {
    const auto &r{obj->getRenderable()};
    Shaders::_3D::COLTEX.vao.bindEBO(r.ebo);
    Shaders::_3D::COLTEX.vao.bindVBO(r.sharedVBO);

    Shaders::_3D::COLTEX.setMat4("model", obj->getTransform());
    Shaders::_3D::COLTEX.setMat4("view", mainCamera.getView());

    r.writeToSharedVBO();

    atlas->bindTextureUnit();
    Shaders::_3D::COLTEX.vao.bindVertexArray();
    glDrawElements(
        mainPrimitive,
        static_cast<GLsizei>(Shaders::_3D::COLTEX.vao.boundedEBO->size),
        GL_UNSIGNED_INT, 0);
  }
}