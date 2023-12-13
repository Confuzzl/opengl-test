export module wrapper.program.global_programs;

import wrapper.program.programs;

export namespace Programs {
constinit Col COL_PROGRAM{};
constinit Tex TEX_PROGRAM{};
constinit ColTex COLTEX_PROGRAM{};
constinit Font FONT_PROGRAM{};

void createAll() {
  COL_PROGRAM.create();
  TEX_PROGRAM.create();
  COLTEX_PROGRAM.create();
  FONT_PROGRAM.create();
}
} // namespace Programs