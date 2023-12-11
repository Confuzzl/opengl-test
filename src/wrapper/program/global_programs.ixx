export module wrapper.program.global_programs;

import wrapper.program.programs;

export namespace Programs {
Col COL_PROGRAM{};
Tex TEX_PROGRAM{};
ColTex COLTEX_PROGRAM{};
Font FONT_PROGRAM{};

void createAll() {
  COL_PROGRAM.create();
  TEX_PROGRAM.create();
  COLTEX_PROGRAM.create();
  FONT_PROGRAM.create();
}
} // namespace Programs