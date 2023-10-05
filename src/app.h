#pragma once
#include "font.h"
#include "update_cycle.h"
#include "util/gl_utils.h"
#include "util/glm_utils.h"
#include "world/scene.h"
#include "wrapper/program/programs.h"
#include "wrapper/tex_object.h"
#include <stdexcept>

struct App {
  struct FailedWindowCreationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  static const int WIDTH = 1280, HEIGHT = 720;
  static const mat4 UI_MAT;

  GLFWwindow *window;

  UpdateCycle loopCycle{0};
  UpdateCycle updateCycle{1.0 / 120};
  UpdateCycle frameCycle{1.0 / 60};
  unsigned int seconds = 0;

  bool cursorSnap = false;
  double prevX = WIDTH / 2, prevY = HEIGHT / 2;

  DefaultProgram defaultProgram;
  FontProgram fontProgram;

  TexObject atlas;
  Font consolas{"consolas", 16, 32};

  Scene scene{};

  App();
  ~App();

  void processInput();

  void drawScene();
  void drawTextBottomLeft(const float x, const float y, const float scale,
                          const std::string msg);
  void drawTextTopLeft(const float x, const float y, const float scale,
                       const std::string msg);

  void catchException(const std::runtime_error &e);

private:
  void createWindow();
};
extern App app;
