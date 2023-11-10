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
  BaseTextCorner(const BaseTextCorner &) = delete;
  BaseTextCorner(BaseTextCorner &&) = delete;
  BaseTextCorner &operator=(const BaseTextCorner &) = delete;
  BaseTextCorner &operator=(BaseTextCorner &&) = delete;

private:
  const OffsetEquation &xEquation;
  const OffsetEquation &yEquation;
  float textOffsetY;

public:
  void drawText(const std::string &msg);
  void drawText(const float scale, const std::string &msg);
  void drawText(const float x, const float y, const float scale,
                const std::string &msg);
  void drawText(const float x, const float y, const float scale,
                const std::string &msg, bool followOffset, bool addToOffset);

  void resetTextOffset();
};
