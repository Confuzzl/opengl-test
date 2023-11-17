module;

#include "util/gl_utils.hpp"

export module app.app;

import util.glm;
import util.memory;
import util.vector;
import <stdexcept>;

export class UpdateCycle;
export class DefaultProgram;
export class FontProgram;
export class TexObject;
export class Font;
export class Scene;

import rendering.animation;
import rendering.frame.keyframe;

export struct App {
  struct FailedWindowCreationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  static const int WIDTH = 1280, HEIGHT = 720;
  static const Mat4 UI_MAT;

  GLFWwindow *window;

  UPtr<UpdateCycle> loopCycle{std::make_unique<UpdateCycle>(0)};
  UPtr<UpdateCycle> updateCycle{std::make_unique<UpdateCycle>(120)};
  UPtr<UpdateCycle> frameCycle{std::make_unique<UpdateCycle>(60)};
  unsigned int seconds = 0;

  bool cursorSnap = false;
  double prevX = WIDTH / 2, prevY = HEIGHT / 2;

  UPtr<DefaultProgram> defaultProgram{std::make_unique<DefaultProgram>()};
  UPtr<FontProgram> fontProgram{std::make_unique<FontProgram>()};

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
  void processInput();

  float speedMagnitude;
  float rotateMagnitude;
};

export App app{};