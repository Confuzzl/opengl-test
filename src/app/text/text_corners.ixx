export module app.text.text_corners;

import app.text.base_text_corner;

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

export TextBottomLeft BOTTOM_LEFT{};
export TextTopLeft TOP_LEFT{};
export TextBottomRight BOTTOM_RIGHT{};
export TextTopRight TOP_RIGHT{};