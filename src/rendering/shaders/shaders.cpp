module;

#include "util/gl_utils.hpp"

module rendering.shaders;

void Shaders::Base::useProgram() const {
  if (not allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("PROGRAM {} WAS BOUND BEFORE INITIALIZATION", GLid)};
  glUseProgram(GLid);
}

void Shaders::Base::setVec3(const char *name, const Vec3 &vec) const {
  glUniform3fv(glGetUniformLocation(GLid, name), 1, glm::value_ptr(vec));
}
void Shaders::Base::setMat4(const char *name, const Mat4 &matrix) const {
  glUniformMatrix4fv(glGetUniformLocation(GLid, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}