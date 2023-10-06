#include "app.h"
#include "util/debug_utils.h"
#include "world/collision/prism.h"
#include <chrono>

// #include "world/render/face_uv_list.h"
#include "world/collision/simplex.h"

int main() {
  Simplex s{{{-1, -1, 1}, {1, -1, -1}, {1, 1, 1}, {-1, 1, -1}}};

  // Prism a{1, 1, 1};
  // a.rotateZ(45);
  // a.translate({0, 0, -3});

  // Prism b{1, 1, 1};
  // b.translate({5, 0, 0});

  // Prism c{1, 2, 1};
  // c.translate({0, 0, 3});

  // Prism d{3, 1, 2};
  // d.translate({0, 2, 0});

  // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glEnable(GL_DEPTH_TEST);
  // glEnable(GL_CULL_FACE);
  // app.defaultProgram.vao.bindVBO(Prism::sharedVBO);
  // app.defaultProgram.vao.bindEBO(Prism::ebo);

  // glfwSwapInterval(0);
  // while (!glfwWindowShouldClose(app.window)) {
  //   try {
  //     double currTime = glfwGetTime();

  //    app.loopCycle.pushNewTime(currTime);
  //    if (app.updateCycle.pastLength(currTime)) {
  //      app.updateCycle.pushNewTime(currTime);
  //      glfwPollEvents();
  //      app.processInput();
  //    }
  //    if (app.frameCycle.pastLength(currTime)) {
  //      app.frameCycle.pushNewTime(currTime);

  //      glClearColor(0.5, 0.5, 0.5, 1);
  //      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //      app.drawScene();
  //      app.drawTextTopLeft(16, 16, 1, std::format("Time: {:.2f}s",
  //      currTime)); app.drawTextTopLeft(16, 48, 1,
  //                          std::format("LPS: {}",
  //                          app.loopCycle.prevCount));
  //      app.drawTextTopLeft(16, 80, 1,
  //                          std::format("UPS: {}",
  //                          app.updateCycle.prevCount));
  //      app.drawTextTopLeft(16, 112, 1,
  //                          std::format("FPS: {}",
  //                          app.frameCycle.prevCount));

  //      glfwSwapBuffers(app.window);
  //    }
  //    if (currTime - app.seconds >= 1) {
  //      app.seconds++;
  //      app.loopCycle.pushCount();
  //      app.updateCycle.pushCount();
  //      app.frameCycle.pushCount();
  //    }
  //  } catch (const std::runtime_error &e) {
  //    app.catchException(e);
  //  }
  //}
  // std::cout << std::format("app terminated at {:.2f}s\n", glfwGetTime());
  // glfwTerminate();
}
