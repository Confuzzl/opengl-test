module rendering.renderable_col;

bool RenderableCol::exceptionCondition() {
  return indexList.size() != colList.size();
}