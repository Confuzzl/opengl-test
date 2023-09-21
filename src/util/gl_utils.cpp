#include "gl_utils.h"
FailedShaderCompilationException::FailedShaderCompilationException(
    const char *message)
    : std::runtime_error(message) {}
FailedTextureLoadException::FailedTextureLoadException(const char *message)
    : std::runtime_error(message) {}
FailedWindowCreationException::FailedWindowCreationException(
    const char *message)
    : std::runtime_error(message) {}
UnallocatedGLObjectUsageException::UnallocatedGLObjectUsageException(
    const char *message)
    : std::runtime_error(message){};