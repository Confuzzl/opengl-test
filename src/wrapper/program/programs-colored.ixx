export module wrapper.program.programs:colored;

import wrapper.program.base_program;

export class ColoredProgram : public BaseProgram {
public:
  ColoredProgram();

  void defineVAO() override;
};