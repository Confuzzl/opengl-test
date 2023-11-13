module rendering.frame.keyframe;

const Keyframe Keyframe::START{Mat4{1.0f}, 0};

Keyframe::Keyframe(const Mat4 &transform, const double time)
    : Frame(transform), time{time} {}