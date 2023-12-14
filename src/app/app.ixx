module;

#include "util/gl_utils.hpp"

export module app.app;

import world.scene;
import world.entity.player;
import world.camera;
// import wrapper.program.programs;
import util.glm;
import util.memory;
import util.vector;
import <stdexcept>;

export struct UpdateCycle;
export struct TexObject;
export struct Font;

import rendering.anim.animation;
import rendering.anim.frame.keyframe;

export struct App {
  struct FailedWindowCreationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  static const unsigned int WIDTH = 1280, HEIGHT = 720;
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
  unsigned int mainPrimitive = GL_TRIANGLES;

  Animation anim{vector_util::makeVector<UPtr<const Keyframe>>(
      Keyframe::start(), Keyframe::identity(10))};

  App();
  ~App();

  void start();
  void startUpdate(const double t);
  void startFrame(const double t);
  void createWindow();
  void catchException(const std::runtime_error &e);

  void drawScene();
  void processInput(const double dt);

  float speedMagnitude;
  float rotateMagnitude;
};

export App mainApp{};
export Scene &mainScene{*mainApp.scene};
export Player &mainPlayer{*mainScene.player};
export Camera &mainCamera{mainPlayer.getCamera()};