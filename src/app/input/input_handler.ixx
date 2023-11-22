module;

#include "util/gl_utils.hpp"

export module app.input.input_handler;

import app.app;
import world.scene;
import world.entity.player;
import world.camera;
import util.vector;
import util.glm;
import util.debug;
import <map>;
import <functional>;

export struct InputHandler {
  struct Key {
    using Callback = std::function<void(const double)>;

    static Callback NONE() {
      return [](const double) {};
    }

    bool on = false, justOn = false;
    bool justUsed = false;
    const Callback processOn;
    const Callback processJustOn;
    const Callback processOff;
    const Callback processJustOff;

    Key(const Callback &processOn, const Callback &processJustOn,
        const Callback &processOff, const Callback &processJustOff)
        : processOn{processOn}, processJustOn{processJustOn},
          processOff{processOff}, processJustOff{processJustOff} {}
    Key(const Callback &processOn, const Callback &processOff)
        : Key(processOn, processOn, processOff, processOff){};
    Key(const Callback &processOn) : Key(processOn, NONE()) {}

    void change(int action) {
      switch (action) {
      case GLFW_RELEASE: {
        on = false;
        justUsed = true;
      }
      case GLFW_PRESS: {
        on = true;
        justUsed = true;
      }
      case GLFW_REPEAT: {
      }
      }
      // on = b;
      // justOn = b;
    }

    void operator()(const double dt) {
      if (on && justUsed) {
        processJustOn(dt);
        justUsed = false;
      }
      if (on && not justUsed) {
        processOn(dt);
      }
      if (not on && justUsed) {
        processJustOff(dt);
        justUsed = false;
      }
      if (not on && not justUsed) {
        processOff(dt);
      }
    }

    static Callback
    playerMoveFunction(const std::function<Vec3()> &directionSupplier,
                       const double m) {
      return [directionSupplier, m](const double dt) {
        mainPlayer.translate(directionSupplier() * static_cast<float>(dt * m));
      };
    }

    static Callback cameraRotateFunction(const double a, const double b) {
      return [a, b](const double dt) {
        const float sens = mainCamera.getSensitivity();
        mainCamera.rotate(static_cast<float>(sens * dt * a),
                          static_cast<float>(sens * dt * b));
      };
    }
  };

  static std::map<int, Key> keys;

  static void callback(GLFWwindow *window, int key, int scancode, int action,
                       int mods);
};