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
    using ProcessFunction = std::function<void(const double)>;

    const static ProcessFunction NO_PROCESS;

    bool on = false;
    const ProcessFunction processOn;
    const ProcessFunction processOff;

    Key(const ProcessFunction &processOn, const ProcessFunction &processOff)
        : processOn{processOn}, processOff(processOff){};
    Key(const ProcessFunction &processOn) : Key(processOn, NO_PROCESS) {}

    void process(const double dt) const {
      if (on) {
        processOn(dt);
      } else {
        processOff(dt);
      }
    }

    static ProcessFunction
    playerMoveFunction(const std::function<Vec3()> &directionSupplier,
                       const double m) {
      return [directionSupplier, m](const double dt) {
        mainPlayer.translate(directionSupplier() * static_cast<float>(dt * m));
      };
    }

    static ProcessFunction cameraRotateFunction(const double a,
                                                const double b) {
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