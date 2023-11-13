module;

#include "util/gl_utils.hpp"
#include <algorithm>
#include <ranges>

module rendering.animation;

import util.debug;

Animation::Animation(UPtrVector<const Keyframe> &&keyframes)
    : keyframes{std::move(keyframes)} {
  std::ranges::sort(this->keyframes, [](const UPtr<const Keyframe> &k1,
                                        const UPtr<const Keyframe> &k2) {
    return k1->time < k2->time;
  });
  length = this->keyframes.back()->time;
}

void Animation::play() { startTime = glfwGetTime(); }
void Animation::end() {
  pause();
  reset();
  startTime = -1;
}
void Animation::pause() {
  animating = false;
  lastTime = currentTime;
  currentTime = glfwGetTime();
}
void Animation::reset() {
  currentTime = 0;
  lastTime = 0;
}

const Inbetween Animation::getCurrentKeyframe() {
  if (startTime == -1)
    return Inbetween::IDENTITY;
  if (currentTime > length) {
    if (loop)
      reset();
    else
      end();
  }

  if (animating) {
    lastTime = currentTime;
    currentTime = startTime - glfwGetTime();
  } else {
  }

  for (const auto &keyframe : keyframes) {
  }
  return Inbetween::IDENTITY;
}