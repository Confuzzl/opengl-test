module;

#include "util/gl_utils.hpp"
#include <algorithm>
#include <numeric>

module app.app;

import app.update_cycle;
import wrapper.program.programs;
import wrapper.tex_object;
import app.text.font;
import world.game_object;
import wrapper.program.vertex_formats;
import world.render.renderable;
import app.text.text_corners;
import util.vector;
import util.debug;

import app.input.input_handler;

const Mat4 App::UI_MAT{glm::ortho(0.0f, static_cast<float>(App::WIDTH), 0.0f,
                                  static_cast<float>(App::HEIGHT))};

App::App() {
  std::cout << "app constructing\n";
  glfwInit();
  frameCycle->bottleNeck(
      glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate);

  createWindow();

  defaultProgram->create();
  fontProgram->create();

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

  anim.getCurrentKeyframe();
  Text::BOT_LT.drawText(std::format("start: {}", anim.startTime));
  Text::BOT_LT.drawText(
      std::format("time: {:+.2f} {:+.2f}", anim.currentTime, anim.lastTime));
  Text::BOT_LT.drawText(std::format("animating: {}", anim.animating));

  glfwSwapBuffers(window);
}

static void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
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
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetKeyCallback(window, InputHandler::callback);

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
//   if (glfwGetKey(window, GLFW_KEY_ESCAPE))
//     glfwSetWindowShouldClose(window, GL_TRUE);
//
//   if (glfwGetKey(window, GLFW_KEY_1))
//     mainPrimitive = GL_TRIANGLES;
//   if (glfwGetKey(window, GLFW_KEY_2))
//     mainPrimitive = GL_LINE_LOOP;
//   if (glfwGetKey(window, GLFW_KEY_3))
//     mainPrimitive = GL_POINTS;
//
//   if (glfwGetKey(window, GLFW_KEY_Z))
//     anim.play();
//   if (glfwGetKey(window, GLFW_KEY_X))
//     anim.end();
//   if (glfwGetKey(window, GLFW_KEY_C))
//     anim.toggle();
//   if (glfwGetKey(window, GLFW_KEY_V))
//     anim.reset();
//
//   Camera &cam{*app.scene->player->camera};
//
//   speedMagnitude = static_cast<float>(updateCycle->delta * cam.getSpeed());
//   if (glfwGetKey(window, GLFW_KEY_W))
//     cam.addVelocity(cam.getForward() * speedMagnitude);
//   if (glfwGetKey(window, GLFW_KEY_A))
//     cam.addVelocity(cam.getRight() * -speedMagnitude);
//   if (glfwGetKey(window, GLFW_KEY_S))
//     cam.addVelocity(cam.getForward() * -speedMagnitude);
//   if (glfwGetKey(window, GLFW_KEY_D))
//     cam.addVelocity(cam.getRight() * speedMagnitude);
//   if (glfwGetKey(window, GLFW_KEY_SPACE))
//     cam.addVelocity(glm_util::Y_PLUS * speedMagnitude);
//   if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
//     cam.addVelocity(glm_util::Y_PLUS * -speedMagnitude);
//
//   rotateMagnitude =
//       static_cast<float>(updateCycle->delta * cam.getSensitivity());
//   if (glfwGetKey(window, GLFW_KEY_UP))
//     cam.rotate(0, rotateMagnitude);
//   if (glfwGetKey(window, GLFW_KEY_LEFT))
//     cam.rotate(rotateMagnitude, 0);
//   if (glfwGetKey(window, GLFW_KEY_DOWN))
//     cam.rotate(0, -rotateMagnitude);
//   if (glfwGetKey(window, GLFW_KEY_RIGHT))
//     cam.rotate(-rotateMagnitude, 0);
//
//   cam.update();
// }

void App::drawScene() {
  defaultProgram->useProgram();
  defaultProgram->setMat4("projection", mainCamera.getProjection());

  for (const auto &[ID, obj] : mainScene.objectMap) {
    const auto &r{obj->getRenderable()};
    defaultProgram->vao.bindEBO(&r.ebo);
    defaultProgram->vao.bindVBO(&r.sharedVBO);

    defaultProgram->setMat4("model", obj->getTransform());
    defaultProgram->setMat4("view", mainCamera.getView());

    r.writeToSharedVBO();

    atlas->bindTextureUnit();
    defaultProgram->vao.bindVertexArray();
    glDrawElements(mainPrimitive,
                   static_cast<GLsizei>(defaultProgram->vao.boundedEBO->size),
                   GL_UNSIGNED_INT, 0);
  }
}