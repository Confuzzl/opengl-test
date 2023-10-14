export module wrapper.program.programs:simple;

import wrapper.program.base_program;

export class DefaultProgram : public BaseProgram {
public:
  DefaultProgram();

  void defineVAO() override;
};