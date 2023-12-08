export module rendering.anim.frame.keyframe;

import rendering.anim.frame.frame;
import util.memory;
import util.glm;

export struct Keyframe : public Frame {
  const double time;

  Keyframe(const Mat4 &transform, const double time);

  static UPtr<const Keyframe> start();
  static UPtr<const Keyframe> identity(const double time);
  static UPtr<const Keyframe> from(const Mat4 &transform, const double time);
};