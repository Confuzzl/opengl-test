module;

#include "util/gl_utils.hpp"
#include <algorithm>
#include <numeric>

module app.app;

import app.update_cycle;
import wrapper.program.programs;
import wrapper.tex_object;
import app.text.font;
import world.scene;
import wrapper.program.vertex_formats;
import world.render.renderable;
import app.text.text_corners;
import util.vector;
import util.debug;

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
      double currTime = glfwGetTime();

      loopCycle->pushNewTime(currTime);
      if (updateCycle->pastLength(currTime)) {
        updateCycle->pushNewTime(currTime);
        glfwPollEvents();
        processInput();
      }
      if (frameCycle->pastLength(currTime)) {
        frameCycle->pushNewTime(currTime);

        glClearColor(0.5, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawScene();

        Text::resetAllTextOffsets();

        const auto &cam = app.scene->camera;
        const Vec3 &pos = cam->getPosition();
        Text::TOP_LT.drawText(std::format("POS: {:+.3f} {:+.3f} {:+.3f}",
                                          pos[0], pos[1], pos[2]));
        Text::TOP_LT.drawText(std::format("CAM: {:+.3f} {:+.3f}", cam->getYaw(),
                                          cam->getPitch()));

        Text::TOP_RT.drawText(std::format("FPS: {}", frameCycle->prevCount));
        Text::TOP_RT.drawText(std::format("Time: {:.2f}s", currTime));
        Text::TOP_RT.drawText(std::format("LPS: {}", loopCycle->prevCount));
        Text::TOP_RT.drawText(std::format("UPS: {}", updateCycle->prevCount));

        glfwSwapBuffers(window);
      }
      if (currTime - seconds >= 1) {
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

  const float magnitude = static_cast<float>(
      app.updateCycle->delta * app.scene->camera->getSensitivity());
  app.scene->camera->rotate(dx * magnitude, dy * magnitude);
}
// static void keyCallback(GLFWwindow *window, int key, int scancode, int
// action,
//                         int mods) {}

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
  // glfwSetKeyCallback(window, keyCallback);

  gladLoadGL();
  glViewport(0, 0, WIDTH, HEIGHT);
}

void App::catchException(const std::runtime_error &e) {
  std::cout << e.what();
  glfwSetWindowShouldClose(app.window, GL_TRUE);
}

void App::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, GL_TRUE);

  Camera &cam{*app.scene->camera};

  {
    cam.resetVelocity();
    const float magnitude =
        static_cast<float>(updateCycle->delta * cam.getSpeed());
    if (glfwGetKey(window, GLFW_KEY_W))
      cam.addVelocity(cam.getForward() * magnitude);
    if (glfwGetKey(window, GLFW_KEY_A))
      cam.addVelocity(cam.getRight() * -magnitude);
    if (glfwGetKey(window, GLFW_KEY_S))
      cam.addVelocity(cam.getForward() * -magnitude);
    if (glfwGetKey(window, GLFW_KEY_D))
      cam.addVelocity(cam.getRight() * magnitude);
    if (glfwGetKey(window, GLFW_KEY_SPACE))
      cam.addVelocity(Y_PLUS * magnitude);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
      cam.addVelocity(Y_PLUS * -magnitude);
  }
  {
    const float magnitude =
        static_cast<float>(updateCycle->delta * cam.getSensitivity());
    if (glfwGetKey(window, GLFW_KEY_UP))
      cam.rotate(0, magnitude);
    if (glfwGetKey(window, GLFW_KEY_LEFT))
      cam.rotate(magnitude, 0);
    if (glfwGetKey(window, GLFW_KEY_DOWN))
      cam.rotate(0, -magnitude);
    if (glfwGetKey(window, GLFW_KEY_RIGHT))
      cam.rotate(-magnitude, 0);
  }

  cam.update();
}

void App::drawScene() {
  defaultProgram->useProgram();
  defaultProgram->setMat4("projection", app.scene->camera->getProjection());

  for (const auto &[ID, obj] : app.scene->objectMap) {
    const auto &r = obj->getRenderable();
    defaultProgram->vao.bindEBO(r.ebo);
    defaultProgram->vao.bindVBO(r.sharedVBO);

    defaultProgram->setMat4("model", obj->getTransform());
    defaultProgram->setMat4("view", app.scene->camera->getView());

    r.writeToSharedVBO();

    atlas->bindTextureUnit();
    defaultProgram->vao.bindVertexArray();
    unsigned int primitive;
    primitive = GL_POINTS;
    // primitive = GL_LINE_STRIP;
    //  primitive = GL_TRIANGLES;
    glDrawElements(primitive,
                   static_cast<GLsizei>(defaultProgram->vao.boundedEBO.size),
                   GL_UNSIGNED_INT, 0);
  }
}