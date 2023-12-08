export module rendering.anim.frame.frame;

import util.glm;

export struct Frame {
  const Mat4 transform;

  Frame(const Mat4 &transform);
};