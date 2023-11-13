export module rendering.animation;

import util.memory;
import rendering.frame.keyframe;
import rendering.frame.inbetween;
import util.glm;
import <stdexcept>;

export struct Animation {
  // struct KeyframeAccessBeforeStartException : public std::runtime_error {
  //   using std::runtime_error::runtime_error;
  // };

  std::string name;

  UPtrVector<const Keyframe> keyframes;
  double length;

  const bool loop = true;
  // const unsigned int maxIterations;
  // unsigned int iterations = 0;

  double startTime = -1;
  double currentTime = 0, lastTime = 0;
  bool animating = false;

  Animation(UPtrVector<const Keyframe> &&keyframes);

  void play();
  void end();
  void pause();
  void reset();

  const Inbetween getCurrentKeyframe();
};