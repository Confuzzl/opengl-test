module;

#include "util/gl_utils.hpp"

export module app.app;

import world.scene;
import world.entity.player;
import world.camera;
import util.glm;
import util.memory;
import util.vector;
import <stdexcept>;

export struct UpdateCycle;
export struct TexObject;
export struct Font;

import rendering.anim.animation;
import rendering.anim.frame.keyframe;

import app.rendering_handler;

export struct App {
  struct FailedWindowCreationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  static constexpr unsigned int WIDTH = 1280, HEIGHT = 720;
  static const Mat4 UI_MAT;

  GLFWwindow *window;

  UPtr<UpdateCycle> loopCycle;
  UPtr<UpdateCycle> updateCycle;
  UPtr<UpdateCycle> frameCycle;
  unsigned int seconds = 0;

  bool cursorSnap = false;
  double prevX = WIDTH / 2, prevY = HEIGHT / 2;

  // UPtr<Programs::ColTex> colTexProgram{std::make_unique<Programs::ColTex>()};
  // UPtr<Shaders::_2D::FONT>
  // fontProgram{std::make_unique<Shaders::_2D::FONT>()};

  UPtr<TexObject> atlas{std::make_unique<TexObject>("atlas")};
  UPtr<Font> consolas{std::make_unique<Font>("consolas1024", 64, 128)};

  UPtr<Scene> scene{std::make_unique<Scene>()};

  RenderingHandler renderingHandler{};

  // Animation anim{vector_util::makeVector<UPtr<const Keyframe>>(
  //     Keyframe::start(), Keyframe::identity(10))};

  App();
  ~App();

  void createWindow();
  void catchException(const std::runtime_error &e);

  void start();
  void startUpdate(const double t);
  void processInput(const double dt);
  void startFrame(const double t);
};

export App mainApp{};
export Scene &mainScene{*mainApp.scene};
export Player &mainPlayer{*mainScene.player};
export Camera &mainCamera{mainPlayer.getCamera()};