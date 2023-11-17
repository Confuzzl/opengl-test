module;

#include "util/gl_utils.hpp"
#include <algorithm>
#include <numeric>

module app.app;

import app.update_cycle;
import wrapper.program.programs;
import wrapper.tex_object;
import app.text.font;
import world.camera;
import world.scene;
import world.entity.player;
import world.game_object;
import wrapper.program.vertex_formats;
import world.render.renderable;
import app.text.text_corners;
import util.vector;
import util.debug;

import app.input.key;

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
  std::cout << "app terminated\n";
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
  // processInput();
}
void App::startFrame(const double t) {
  frameCycle->pushNewTime(t);

  glClearColor(0, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawScene();

  Text::resetAllTextOffsets();

  const Camera &cam = *app.scene->player->camera;
  const Vec3 &pos = cam.getPosition();
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
  if (not app.cursorSnap) {
    app.prevX = xpos;
    app.prevY = ypos;
    app.cursorSnap = true;
  }
  const float dx = static_cast<float>(app.prevX - xpos);
  const float dy = static_cast<float>(app.prevY - ypos);
  app.prevX = xpos;
  app.prevY = ypos;

  Camera &cam{*app.scene->player->camera};

  const float magnitude =
      static_cast<float>(app.updateCycle->delta * cam.getSensitivity());
  cam.rotate(dx * magnitude, dy * magnitude);
}

// static void keyCallback(GLFWwindow *window, int key, int scancode, int
// action,
//                         int mods) {
//   if (key == GLFW_KEY_ESCAPE)
//     glfwSetWindowShouldClose(window, GL_TRUE);
//
//   if (key == GLFW_KEY_1 && action == GLFW_PRESS)
//     app.mainPrimitive = GL_TRIANGLES;
//   if (key == GLFW_KEY_2 && action == GLFW_PRESS)
//     app.mainPrimitive = GL_LINE_LOOP;
//   if (key == GLFW_KEY_3 && action == GLFW_PRESS)
//     app.mainPrimitive = GL_POINTS;
//
//   if (key == GLFW_KEY_Z && action == GLFW_PRESS)
//     app.anim.play();
//   if (key == GLFW_KEY_X && action == GLFW_PRESS)
//     app.anim.end();
//   if (key == GLFW_KEY_C && action == GLFW_PRESS)
//     app.anim.toggle();
//   if (key == GLFW_KEY_V && action == GLFW_PRESS)
//     app.anim.reset();
//
//   Camera &cam{*app.scene->camera};
//
//   {
//     cam.resetVelocity();
//     const float magnitude =
//         static_cast<float>(app.updateCycle->delta * cam.getSpeed());
//     if (key == GLFW_KEY_W)
//       cam.addVelocity(cam.getForward() * magnitude);
//     if (key == GLFW_KEY_A)
//       cam.addVelocity(cam.getRight() * -magnitude);
//     if (key == GLFW_KEY_S)
//       cam.addVelocity(cam.getForward() * -magnitude);
//     if (key == GLFW_KEY_D)
//       cam.addVelocity(cam.getRight() * magnitude);
//     if (key == GLFW_KEY_SPACE)
//       cam.addVelocity(Y_PLUS * magnitude);
//     if (key == GLFW_KEY_LEFT_CONTROL)
//       cam.addVelocity(Y_PLUS * -magnitude);
//   }
//   {
//     const float magnitude =
//         static_cast<float>(app.updateCycle->delta * cam.getSensitivity());
//     if (key == GLFW_KEY_UP)
//       cam.rotate(0, magnitude);
//     if (key == GLFW_KEY_LEFT)
//       cam.rotate(magnitude, 0);
//     if (key == GLFW_KEY_DOWN)
//       cam.rotate(0, -magnitude);
//     if (key == GLFW_KEY_RIGHT)
//       cam.rotate(-magnitude, 0);
//   }
//
//   cam.update();
// }

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
  // glfwSetKeyCallback(window, /*keyCallback*/ Key::foo);

  gladLoadGL();
  glViewport(0, 0, WIDTH, HEIGHT);
}

void App::catchException(const std::runtime_error &e) {
  std::cout << e.what();
  glfwSetWindowShouldClose(app.window, GL_TRUE);
}

// void App::processInput() {
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
  const Camera &cam{*scene->player->camera};

  defaultProgram->useProgram();
  defaultProgram->setMat4("projection", cam.getProjection());

  for (const auto &[ID, obj] : app.scene->objectMap) {
    const auto &r = obj->getRenderable();
    defaultProgram->vao.bindEBO(&r.ebo);
    defaultProgram->vao.bindVBO(&r.sharedVBO);

    defaultProgram->setMat4("model", obj->getTransform());
    defaultProgram->setMat4("view", cam.getView());

    r.writeToSharedVBO();

    atlas->bindTextureUnit();
    defaultProgram->vao.bindVertexArray();
    glDrawElements(mainPrimitive,
                   static_cast<GLsizei>(defaultProgram->vao.boundedEBO->size),
                   GL_UNSIGNED_INT, 0);
  }
}