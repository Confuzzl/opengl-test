export module app.text.base_text_corner;

import <functional>;
import <string>;
import app.app;
import wrapper.program.programs;

export class BaseTextCorner {
protected:
  using OffsetEquation =
      std::function<float(const float, const float, const std::string)>;
  static const OffsetEquation xNormal;
  static const OffsetEquation xShift;
  static const OffsetEquation yNormal;
  static const OffsetEquation yShift;
  BaseTextCorner(const OffsetEquation &xEquation,
                 const OffsetEquation &yEquation);

private:
  const OffsetEquation &xEquation;
  const OffsetEquation &yEquation;
  float textOffset;

public:
  void drawTextRelative(const float scale, const std::string msg);
  void drawTextRelative(const float xOffset, const float yOffset,
                        const float scale, const std::string msg);

  void resetTextOffset();
};
