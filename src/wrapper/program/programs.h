#pragma once
#include "base_program.h"
class DefaultProgram : public BaseProgram {
public:
  DefaultProgram();

  void defineVAO() override;
  void create() override;
};
class FontProgram : public BaseProgram {
public:
  static const int CHAR_WIDTH = 16, CHAR_HEIGHT = 32;
  FontProgram();

  void defineVAO() override;
  void create() override;
};