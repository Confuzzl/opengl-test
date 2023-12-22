module;

#include "util/gl_utils.hpp"
#include <algorithm>
#include <numeric>

module app.app;

import app.update_cycle;
import wrapper.tex_object;
import app.text.font;

import rendering.shaders.global;

import app.input.input_handler;

import util.vector;
import util.debug;

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

  Shaders::createAll();

  try {
    atlas->initTexture();
    consolas->initAtlas();
  } catch (const std::runtime_error &e) {
    catchException(e);
  }

  std::cout << "APP FINISHED CONSTRUCTING\n";
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
  InputHandler::processInput(updateCycle->dt);
}
void App::startFrame(const double t) {
  frameCycle->pushNewTime(t);
  renderingHandler.renderFrame(t);
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