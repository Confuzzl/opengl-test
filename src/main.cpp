#include "util/gl_utils.hpp"

import app.app;
import util.debug;
import world.collision.prism;
import world.factory.simplex_factory;
import world.game_object;
import util.polyhedron;

int main() {
  // try {
  Vec3List coordinates{{-1, -1, +1}, {+1, -1, -1}, {+1, +1, +1}, {-1, +1, -1}};
  for (auto &v : coordinates)
    v /= 2;

  GameObject go{SimplexFactory::createCollidableSimplex(coordinates),
                SimplexFactory::createRenderableSimplex(coordinates)};
  // } catch (const std::runtime_error &e) {
  //   std::cout << e.what();
  // }

  // Prism a{1, 1, 1};
  //  a.rotateZ(45);
  //  a.translate({0, 0, -3});

  Prism b{1, 1, 1};
  b.translate({5, 0, 0});

  Prism c{1, 2, 1};
  c.translate({0, 0, 3});

  Prism d{3, 1, 2};
  d.translate({0, 2, 0});

  glLineWidth(5);
  glPolygonMode(GL_FRONT, GL_FILL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  //  app.defaultProgram.vao.bindVBO(Prism::sharedVBO);
  //  app.defaultProgram.vao.bindEBO(Prism::ebo);
  // app.defaultProgram.vao.bindVBO(SimplexFactory::sharedVBO);
  // app.defaultProgram.vao.bindEBO(SimplexFactory::ebo);

  glfwSwapInterval(0);
  while (!glfwWindowShouldClose(app.window)) {
    try {
      double currTime = glfwGetTime();

      app.loopCycle.pushNewTime(currTime);
      if (app.updateCycle.pastLength(currTime)) {
        app.updateCycle.pushNewTime(currTime);
        glfwPollEvents();
        app.processInput();
      }
      if (app.frameCycle.pastLength(currTime)) {
        app.frameCycle.pushNewTime(currTime);

        glClearColor(0.5, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        app.drawScene();
        app.drawTextTopLeft(16, 16, 1, std::format("Time: {:.2f}s", currTime));
        app.drawTextTopLeft(16, 48, 1,
                            std::format("LPS: {}", app.loopCycle.prevCount));
        app.drawTextTopLeft(16, 80, 1,
                            std::format("UPS: {}", app.updateCycle.prevCount));
        app.drawTextTopLeft(16, 112, 1,
                            std::format("FPS: {}", app.frameCycle.prevCount));

        const auto &pos = app.scene.camera.getPosition();
        app.drawTextTopLeft(16, 144, 1, std::format("X: {:+.3f}", pos[0]));
        app.drawTextTopLeft(16, 176, 1, std::format("Y: {:+.3f}", pos[1]));
        app.drawTextTopLeft(16, 208, 1, std::format("Z: {:+.3f}", pos[2]));

        glfwSwapBuffers(app.window);
      }
      if (currTime - app.seconds >= 1) {
        app.seconds++;
        app.loopCycle.pushCount();
        app.updateCycle.pushCount();
        app.frameCycle.pushCount();
      }
    } catch (const std::runtime_error &e) {
      app.catchException(e);
    }
  }
  std::cout << std::format("app terminated at {:.2f}s\n", glfwGetTime());
  glfwTerminate();
}
