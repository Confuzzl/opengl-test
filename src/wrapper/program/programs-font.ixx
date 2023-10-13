export module wrapper.program.programs:font;

import wrapper.program.base_program;

export class FontProgram : public BaseProgram {
public:
  static const int CHAR_WIDTH = 16, CHAR_HEIGHT = 32;
  FontProgram();

  void defineVAO() override;
};