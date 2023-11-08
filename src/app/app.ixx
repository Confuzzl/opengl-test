module;

#include "util/gl_utils.hpp"

export module app.app;

import app.text.font;
import wrapper.tex_object;
import app.update_cycle;
import util.glm;
import world.scene;
import wrapper.program.programs;
import <stdexcept>;

export struct App {
  struct FailedWindowCreationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  static const int WIDTH = 1280, HEIGHT = 720;
  static const Mat4 UI_MAT;

  GLFWwindow *window;

  UpdateCycle loopCycle;
  UpdateCycle updateCycle;
  UpdateCycle frameCycle;
  unsigned int seconds = 0;

  bool cursorSnap = false;
  double prevX = WIDTH / 2, prevY = HEIGHT / 2;

  DefaultProgram defaultProgram;
  FontProgram fontProgram;

  TexObject atlas;
  Font consolas;

  Scene scene{};

  App();
  ~App();

  void start();
  void createWindow();
  void catchException(const std::runtime_error &e);

  void drawScene();
  void processInput();
};

export App app{};
export Scene &appScene = app.scene;