export module rendering.anim.frame.inbetween;

import rendering.anim.frame.frame;
import rendering.anim.frame.keyframe;

export struct Inbetween : public Frame {
  static const Inbetween IDENTITY;

  using Frame::Frame;
};