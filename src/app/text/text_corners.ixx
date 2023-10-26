export module app.text.text_corners;

import app.text.base_text_corner;

export namespace Text {
class TextBottomLeft : public BaseTextCorner {
public:
  TextBottomLeft() : BaseTextCorner(xNormal, yNormal) {}
};

class TextTopLeft : public BaseTextCorner {
public:
  TextTopLeft() : BaseTextCorner(xNormal, yShift) {}
};

class TextBottomRight : public BaseTextCorner {
public:
  TextBottomRight() : BaseTextCorner(xShift, yNormal) {}
};

class TextTopRight : public BaseTextCorner {
public:
  TextTopRight() : BaseTextCorner(xShift, yShift) {}
};

export TextBottomLeft BOT_LT{};
export TextTopLeft TOP_LT{};
export TextBottomRight BOT_RT{};
export TextTopRight TOP_RT{};

export void resetAllTextOffsets() {
  BOT_LT.resetTextOffset();
  TOP_LT.resetTextOffset();
  BOT_RT.resetTextOffset();
  TOP_RT.resetTextOffset();
}

export void test() {
  TOP_LT.drawText(2, "top left");
  TOP_LT.drawText("top left");
  BOT_LT.drawText(2, "bottom left");
  BOT_LT.drawText("bottom left");
  BOT_RT.drawText(2, "bottom right");
  BOT_RT.drawText("bottom right");
  TOP_RT.drawText(2, "top right");
  TOP_RT.drawText("top right");
}
}; // namespace Text
